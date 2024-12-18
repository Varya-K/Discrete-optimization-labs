#pragma once
#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <fstream>
#include <sstream>

std::vector<std::unordered_set<int>> read_graph_file(std::string filename) {
    std::vector<std::unordered_set<int>> adjacency_list;
    std::ifstream fin(filename);
    std::string line;
    int vertices = 0, edges = 0;
    while (std::getline(fin, line))
    {
        if (line[0] == 'c')
        {
            continue;
        }

        std::stringstream line_input(line);
        char command;
        if (line[0] == 'p')
        {
            std::string type;
            line_input >> command >> type >> vertices >> edges;
            adjacency_list.resize(vertices);
        }
        else
        {
            int start, finish;
            line_input >> command >> start >> finish;
            adjacency_list[start - 1].insert(finish - 1);
            adjacency_list[finish - 1].insert(start - 1);
        }
    }
    return adjacency_list;
}
