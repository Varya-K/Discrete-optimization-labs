#include "GreedyGraphColoring.h"
#include "GreadyRandomizedMCP.h"
#include "LocalSearchMCP.h"
#include "BranchAndBoundMCP.h"
#include <iostream>


void greedy_graph_coloring() {
    std::vector<std::string> files = { "myciel3.col", "myciel7.col", "school1.col", "school1_nsh.col", "anna.col",
           "miles1000.col", "miles1500.col", "le450_5a.col", "le450_15b.col", "queen11_11.col" };
    std::ofstream fout("color.csv");
    fout << "Instance; Colors; Time (sec)\n";
    std::cout << "Instance; Colors; Time (sec)\n";
    for (std::string file : files)
    {
        GreedyGraphColoring problem(R"(D:\Уроки\Магистратура\Дискретная оптимизация\vertex_coloring\)"+file);
        clock_t start = clock();
        problem.find_graph_coloring();
        if (!problem.Check())
        {
            fout << "*** WARNING: incorrect coloring: ***\n";
            std::cout << "*** WARNING: incorrect coloring: ***\n";
        }
        clock_t finish = clock();
        fout << file << "; " << problem.get_colors_count() << "; " << double(finish - start) / 1000 << '\n';
        std::cout << file << "; " << problem.get_colors_count() << "; " << double(finish - start) / 1000 << '\n';
    }
    fout.close();
}

void greedy_randomized_clique() {
    std::vector<std::string> files = { "brock200_1.clq", "brock200_2.clq", "brock200_3.clq", "brock200_4.clq",
        "brock400_1.clq", "brock400_2.clq", "brock400_3.clq", "brock400_4.clq",
        "C125.9.clq", "gen200_p0.9_44.clq", "gen200_p0.9_55.clq",  "hamming8-4.clq",
        "johnson16-2-4.clq", "johnson8-2-4.clq", "keller4.clq", "MANN_a27.clq", "MANN_a9.clq",
        "p_hat1000-1.clq", "p_hat1000-2.clq",  "p_hat1500-1.clq", "p_hat300-3.clq", "p_hat500-3.clq",
        "san1000.clq", "sanr200_0.9.clq", "sanr400_0.7.clq"};
    std::ofstream fout("clique.csv");
    fout << "Instance; Clique; Time (sec)\n";
    std::cout << "Instance; Clique; Time (sec)\n";
    int iterations = 60000;
    for (std::string file : files)
    {
        GreedyRandomizedClique problem(R"(D:\Уроки\Магистратура\Дискретная оптимизация\max_clique_txt\DIMACS_all_ascii\)" + file);
        clock_t start = clock();
        problem.find_clique(iterations);
        if (!problem.Check())
        {
            std::cout << "*** WARNING: incorrect clique ***\n";
            fout << "*** WARNING: incorrect clique ***\n";
        }
        clock_t finish = clock();
        fout << file << "; " << problem.get_clique().size() << "; " << double(clock() - start) / 1000 << '\n';
        std::cout << file << ", result - " << problem.get_clique().size() << ", time - " << double(clock() - start) / 1000 << '\n';
    }
    fout.close();
}


void local_search_clique() {
    std::vector<std::string> files = { "brock200_1.clq", "brock200_2.clq", "brock200_3.clq", "brock200_4.clq",
        "brock400_1.clq", "brock400_2.clq", "brock400_3.clq", "brock400_4.clq",
        "C125.9.clq", "gen200_p0.9_44.clq", "gen200_p0.9_55.clq",  "hamming8-4.clq",
        "johnson16-2-4.clq", "johnson8-2-4.clq", "keller4.clq", "MANN_a27.clq", "MANN_a9.clq",
        "p_hat1000-1.clq", "p_hat1000-2.clq",  "p_hat1500-1.clq", "p_hat300-3.clq", "p_hat500-3.clq",
        "san1000.clq", "sanr200_0.9.clq", "sanr400_0.7.clq" };
    std::ofstream fout("clique_tabu.csv");
    fout << "Instance; Clique; Time (sec)\n";
    std::cout << "Instance; Clique; Time (sec)\n";
    int iterations = 5000;
    for (std::string file : files)
    {
        LocalSearchClique problem(R"(D:\Уроки\Магистратура\Дискретная оптимизация\max_clique_txt\DIMACS_all_ascii\)" + file);
        clock_t start = clock();
        problem.find_clique(iterations);
        if (!problem.Check())
        {
            std::cout << "*** WARNING: incorrect clique ***\n";
            fout << "*** WARNING: incorrect clique ***\n";
        }
        clock_t finish = clock();
        fout << file << "; " << problem.get_clique().size() << "; " << double(clock() - start) / 1000 << '\n';
        std::cout << file << ", result - " << problem.get_clique().size() << ", time - " << double(clock() - start) / 1000 << '\n';
    }
    fout.close();
}



void bnb_clique() {
    std::vector<std::string> files = { "brock200_1.clq","brock200_2.clq", "brock200_3.clq", "brock200_4.clq",
        "C125.9.clq", "gen200_p0.9_44.clq", "gen200_p0.9_55.clq",  "hamming8-4.clq",
        "johnson16-2-4.clq", "johnson8-2-4.clq", "keller4.clq", "MANN_a27.clq", "MANN_a9.clq",
        "p_hat1000-1.clq",  "p_hat1500-1.clq", "p_hat300-3.clq", "san1000.clq", "sanr200_0.9.clq"};
    std::ofstream fout("clique_bnb.csv");
    fout << "Instance; Clique; Time (sec)\n";
    std::cout << "Instance; Clique; Time (sec)\n";
    int iterations = 5000;
    for (std::string file : files)
    {
        BnBClique problem(R"(D:\Уроки\Магистратура\Дискретная оптимизация\max_clique_txt\DIMACS_all_ascii\)" + file);
        clock_t start = clock();
        problem.find_clique(5000);
        if (!problem.Check())
        {
            std::cout << "*** WARNING: incorrect clique ***\n";
            fout << "*** WARNING: incorrect clique ***\n";
        }
        clock_t finish = clock();
        fout << file << "; " << problem.get_clique().size() << "; " << double(clock() - start) / 1000 << '\n';
        std::cout << file << ", result - " << problem.get_clique().size() << ", time - " << double(clock() - start) / 1000 << '\n';
    }
    fout.close();
}

int main()
{
    //greedy_graph_coloring();
}
