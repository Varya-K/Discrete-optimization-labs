#pragma once
#include "LocalSearchMCP.h"
#include <list>
#include <deque>

class BnBClique {
private:
	std::vector<std::unordered_set<int>> adjacency_list;
	std::vector<int> best_clique;
	std::vector<int> pardalos_order;
	std::vector<int> clique;
	int counter = 0;
	int n;

	static int GetRandom(int a, int b)
	{
		static std::mt19937 generator;
		std::uniform_int_distribution<int> uniform(a, b);
		return uniform(generator);
	}

	void run_heuristic(int iterations) {
		LocalSearchClique local_search(adjacency_list);
		local_search.find_clique(iterations);
		best_clique = local_search.get_clique();
	}

	void build_pardalos_order() {
		pardalos_order.resize(n);
		std::vector<int> vertex_degree(n);
		for (int i = 0; i < n; i++) {
			vertex_degree[i] = adjacency_list[i].size();
		}
		for (int i = 0; i < n; i++) {
			auto min_iter = std::min_element(vertex_degree.begin(), vertex_degree.end());
			int vertex = std::distance(vertex_degree.begin(), min_iter);

			pardalos_order[i] = vertex;
			for (int neighbour : adjacency_list[vertex]) {
				vertex_degree[neighbour]--;
			}
			vertex_degree[vertex] = 100000;
		}
	}


	std::vector<std::deque<int>> build_color_order(const std::vector<int>& candidates) {
		std::vector<std::deque<int>>color_order;
		for (int i = candidates.size() - 1; i >= 0; i--) {
			int vertex = candidates[i];
			int vertex_color=-1;
			for (int color = 0; color < color_order.size();color++) {
				bool flag = true;
				for (int v : color_order[color]) {
					if (adjacency_list[vertex].contains(v)) {
						flag=false;
						break;
					}
				}
				if (flag) {
					vertex_color = color;
					break;
				}
			}
			if (vertex_color == -1) {
				color_order.push_back({ vertex });
			}
			else {
				color_order[vertex_color].push_front(vertex);
			}
		}
		return color_order;
	}

	void bnb_recursive(const std::vector<int>& candidates) {
		if (candidates.empty()) {
			if (clique.size() > best_clique.size()) {
				best_clique = clique;
			}
			return;
		}
		std::unordered_set<int> candidates_set(candidates.begin(), candidates.end());
		std::vector<std::deque<int>> color_order = build_color_order(candidates);
		for (int color = color_order.size() - 1; color >= 0; color--) {
			if (clique.size() + color + 1 <= best_clique.size()) {
				return;
			}
			for (int vertex : color_order[color]) {
				clique.push_back(vertex);
				candidates_set.erase(vertex);
				std::vector<int> new_candidates;
				for (int v : candidates_set) {
					if (adjacency_list[vertex].contains(v)) {
						new_candidates.push_back(v);
					}
				}
				bnb_recursive(new_candidates);
				clique.pop_back();
			}
		}
	}

public:
	BnBClique(std::string filename) {
		adjacency_list = read_graph_file(filename);
		n = adjacency_list.size();
	}

	void find_clique(int iterations) {
		run_heuristic(5000);
		clique.clear();
		build_pardalos_order();
		bnb_recursive(pardalos_order);
	}

	std::vector<int> get_clique() const {
		return best_clique;
	}


	bool Check()
	{
		if (std::unique(best_clique.begin(), best_clique.end()) != best_clique.end())
		{
			std::cout << "Duplicated vertices in the clique\n";
			return false;
		}
		for (int i : best_clique)
		{
			for (int j : best_clique)
			{
				if (i != j && !adjacency_list[i].contains(j))
				{
					std::cout << "Returned subgraph is not a clique\n";
					return false;
				}
			}
		}
		return true;
	}
};