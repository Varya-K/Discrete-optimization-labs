#pragma once
#include "Graph.h"
#include <algorithm>
#include <queue>
#include <random>


class LocalSearchClique {
private:
	std::vector<std::unordered_set<int>> neighbour_sets;
	std::vector<std::unordered_set<int>> non_neighbour_sets;
	int n;
	std::vector<int> qco;
	std::vector<int> vertex_qco_index;
	std::vector<int> tau;
	int q_border = 0;
	int c_border = 0;
	std::vector<int> best_clique;

	struct TabuList {
		int max_size = 0;
		std::queue<int> queue;
		std::unordered_set<int> vertexes;
		void add(int vertex) {
			queue.push(vertex);
			vertexes.insert(vertex);
			if (queue.size() > max_size) {
				vertexes.erase(queue.front());
				queue.pop();
			}
		}
		bool is_vertex_in_tabu_list(int vertex) {
			return vertexes.contains(vertex);
		}
		void clear() {
			queue = std::queue<int>();
			vertexes.clear();
		}

	};
	TabuList clique_tabu_list;
	TabuList other_tabu_list;


	static int GetRandom(int a, int b)
	{
		static std::mt19937 generator;
		std::uniform_int_distribution<int> uniform(a, b);
		return uniform(generator);
	}

	void swap_vertexes(int vertex, int border) {
		int vertex_at_border = qco[border];
		std::swap(qco[vertex_qco_index[vertex]], qco[border]);
		std::swap(vertex_qco_index[vertex], vertex_qco_index[vertex_at_border]);
	}

	void insert_to_clique(int vertex)
	{
		for (int non_neighbour : non_neighbour_sets[vertex])
		{
			if (tau[non_neighbour] == 0)
			{
				c_border--;
				swap_vertexes(non_neighbour, c_border);
			}
			tau[non_neighbour]++;
		}
		swap_vertexes(vertex, q_border);
		q_border++;
	}

	void remove_from_clique(int vertex)
	{
		for (int non_neighbour : non_neighbour_sets[vertex])
		{
			if (tau[non_neighbour] == 1)
			{
				swap_vertexes(non_neighbour, c_border);
				c_border++;
			}
			tau[non_neighbour]--;
		}
		q_border--;
		swap_vertexes(vertex, q_border);
	}

	bool swap_1to1()
	{
		for (int clique_i = 0; clique_i < q_border; ++clique_i)
		{
			if (clique_tabu_list.is_vertex_in_tabu_list(qco[clique_i])) continue;
			int vertex = qco[clique_i];
			std::vector<int> candidates_to_swap;
			for (int non_neighbour : non_neighbour_sets[vertex])
			{
				if (tau[non_neighbour] == 1 && !other_tabu_list.is_vertex_in_tabu_list(non_neighbour))
				{
					candidates_to_swap.push_back(non_neighbour);
				}
			}
			if (!candidates_to_swap.empty()) {
				int vertex_to_swap = candidates_to_swap[GetRandom(0, candidates_to_swap.size() - 1)];
				remove_from_clique(vertex);
				insert_to_clique(vertex_to_swap);
				other_tabu_list.add(vertex);
				clique_tabu_list.add(vertex_to_swap);
				return true;
			}
		}
		return false;
	}

	bool move()
	{
		if (c_border == q_border)
			return false;
		int vertex = qco[GetRandom(q_border, c_border - 1)];
		insert_to_clique(vertex);
		return true;
	}

	void clear_clique() {
		clique_tabu_list.clear();
		other_tabu_list.clear();
		tau = std::vector<int>(n, 0);
		qco.resize(n);
		vertex_qco_index.resize(n);
		for (int i = 0; i < n; i++) {
			qco[i] = i;
			vertex_qco_index[i] = i;
		}
		q_border = 0;
		c_border = n;
	}

	void build_non_neighbour_sets() {
		n = neighbour_sets.size();
		non_neighbour_sets.resize(n);
		for (int v1 = 0; v1 < n - 1; v1++) {
			for (int v2 = v1 + 1; v2 < n; v2++) {
				if (!neighbour_sets[v1].contains(v2)) {
					non_neighbour_sets[v1].insert(v2);
					non_neighbour_sets[v2].insert(v1);
				}
			}
		}
		clique_tabu_list.max_size = std::max(static_cast<int>(log2(n)) / 2, 1);
		other_tabu_list.max_size = std::max(static_cast<int>(log2(n)), 1);
	}


public:
	LocalSearchClique(std::string filename) {
		neighbour_sets = read_graph_file(filename);
		build_non_neighbour_sets();
	}

	LocalSearchClique(const std::vector<std::unordered_set<int>>& adjacency_list) : neighbour_sets(adjacency_list) {
		build_non_neighbour_sets();
	}



	void find_clique(int iterations) {
		best_clique.clear();
		for (int i = 0; i < iterations; i++) {
			clear_clique();

			int swaps = 0;
			while (swaps < n/4)
			{
				if (!move())
				{
					if (!swap_1to1())
					{
						break;
					}
					else
					{
						++swaps;
					}
				}
			}
			if (q_border > best_clique.size())
			{
				best_clique.clear();
				std::copy(qco.begin(), qco.begin() + q_border, std::back_inserter(best_clique));
			}
		}
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
				if (i != j && !neighbour_sets[i].contains(j))
				{
					std::cout << "Returned subgraph is not a clique\n";
					return false;
				}
			}
		}
		return true;
	}
};
