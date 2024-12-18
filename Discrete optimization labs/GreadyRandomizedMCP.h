#pragma once
#include "Graph.h"
#include <algorithm>
#include <random>

class GreedyRandomizedClique {
private:
	std::vector<std::unordered_set<int>> adjacency_list;
	std::vector<int> best_clique;

	static int GetRandom(int a, int b)
	{
		static std::mt19937 generator;
		std::uniform_int_distribution<int> uniform(a, b);
		return uniform(generator);
	}

public:
	GreedyRandomizedClique(std::string filename) {
		adjacency_list = read_graph_file(filename);
	}

	

	void find_clique(int iterations) {
		int n = adjacency_list.size();
		best_clique.clear();

		for (int i = 0; i < iterations; i++) {
			std::vector<int> clique;
			std::vector<int> candidates(n);
			for (int i = 0; i < n; ++i)
			{
				candidates[i] = i;
			}
			while (!candidates.empty())
			{
				int rnd = GetRandom(0, candidates.size() - 1);
			
				int vertex = candidates[rnd];
				clique.push_back(vertex);
				for (int c = 0; c < candidates.size(); ++c)
				{
					if (!adjacency_list[vertex].contains(candidates[c]))
					{
						std::swap(candidates[c], candidates[candidates.size() - 1]);
						candidates.pop_back();
						--c;
					}
				}
				if (candidates.size() + clique.size() <= best_clique.size()) {
					break;
				}
			}
			if (best_clique.size() < clique.size()) {
				best_clique = clique;
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

