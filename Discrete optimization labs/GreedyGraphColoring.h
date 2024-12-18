#pragma once
#include "Graph.h"

class GreedyGraphColoring {
private:
	std::vector<std::unordered_set<int>> adjacency_list;
	std::vector<int> vertex_color;
	int count_of_colors=0;

	std::vector<int> get_vertex_order() {
		int n = adjacency_list.size();
		std::vector<int> vertex_order(n);
		std::vector<int> vertex_degree(n);
		for (int i = 0; i < n; i++) {
			vertex_degree[i] = adjacency_list[i].size();
		}
		for (int i = n - 1; i >= 0; i--) {
			auto min_iter = std::min_element(vertex_degree.begin(), vertex_degree.end());
			int vertex = std::distance(vertex_degree.begin(), min_iter);

			vertex_order[i] = vertex;
			for (int neighbour : adjacency_list[vertex]) {
				vertex_degree[neighbour]--;
			}
			vertex_degree[vertex] = 100000;
		}
		return vertex_order;
	}

public:
	GreedyGraphColoring(std::string filename) {
		adjacency_list = read_graph_file(filename);
	}

	void find_graph_coloring() {
		int n = adjacency_list.size();
		std::vector<int> vertex_order = get_vertex_order();
		vertex_color = std::vector<int>(n, -1);
		std::vector<std::vector<int>>color_order;
		for (int i = 0; i < n; i++) {
			int vertex = vertex_order[i];
			int v_color = -1;
			for (int color = 0; color < color_order.size(); color++) {
				bool flag = true;
				for (int v : color_order[color]) {
					if (adjacency_list[vertex].contains(v)) {
						flag = false;
						break;
					}
				}
				if (flag) {
					v_color = color;
					break;
				}
			}
			if (v_color == -1) {
				color_order.push_back({ vertex });
				count_of_colors++;
				vertex_color[vertex] = color_order.size() - 1;
			}
			else {
				color_order[v_color].push_back(vertex);
				vertex_color[vertex] = v_color;
			}
		}
	}

	int get_colors_count() const{
		return count_of_colors;
	}

	std::vector<int> get_color_sets() const{
		return vertex_color;
	}

	bool Check()
	{
		for (size_t i = 0; i < adjacency_list.size(); ++i)
		{
			if (vertex_color[i] == -1)
			{
				std::cout << "Vertex " << i + 1 << " is not colored\n";
				return false;
			}
			for (int neighbour : adjacency_list[i])
			{
				if (vertex_color[neighbour] == vertex_color[i])
				{
					std::cout << "Neighbour vertices " << i + 1 << ", " << neighbour + 1 << " have the same color\n";
					return false;
				}
			}
		}
		return true;
	}
};

