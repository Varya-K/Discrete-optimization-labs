# Лабораторные работы по дискретной оптимизации и исследованию операций

- Для четения файлов был создан общий метод, который возвращает список смежности. Файл - "Graph.h"
- Лабораторная 1 - реализация жадной эвристики для решения задачи о раскраске графа. Для этого использовался принцип "smallest degree last with remove". Файл - "GreedyGraphColoring.h". Решение - "color.cvs"
- Лабораторная 2 - реализация жадной рандомизированной эвристики для решения задачи о поиске наибольшей клики в графе. Файл - "GreedyRandomizedMCP.h". Решение - "clique.cvs"
- Лабораторная 3 - реализация локального поиска для решения задачи о поиске наибольшей клики в графе. Для этого использовался tabu-search. Файл - "LocalSearchMCP.h". Решение - "clique_tabu.cvs"
- Лабораторная 4 - реализация метода ветвей и границ для решения задачи о поиске наибольшей клики в графе. В качестве начального значения клики использовался результат локального поиска из лабораторной 3, также был реализован метод ветвей и границ с coloring bounds. Файл - "BranchAndBoundMCP.h". Решение - "clique_bnb.cvs"
- Для запуска тестов были созданы методы в файле "Discrete optimization labs.cpp", в котором также находится и main метод.
