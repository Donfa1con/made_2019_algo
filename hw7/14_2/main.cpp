/*
Дан неориентированный связный граф.
Требуется найти вес минимального остовного дерева в этом графе.
Вариант 2. С помощью алгоритма Крускала.

Формат ввода
Первая строка содержит два натуральных числа n и m —
количество вершин и ребер графа соответственно (1 ≤ n ≤ 20000, 0 ≤ m ≤ 100000).
Следующие m строк содержат описание ребер по одному на строке.
Ребро номер i описывается тремя натуральными числами bi, ei и wi —
номера концов ребра и его вес соответственно (1 ≤ bi, ei ≤ n, 0 ≤ wi ≤ 100000).

Формат вывода
Выведите единственное целое число - вес минимального остовного дерева.
 
Пример
Ввод    Вывод
4 4       7
1 2 1
2 3 2
3 4 5
4 1 4
*/
#include "dsu/dsu.hpp"

#include <iostream>
#include <vector>
#include <algorithm>


using Edge = std::pair<int, std::pair<int, int>>;


int get_mst_size(int n, int m, std::vector<Edge>& graph) {
    int cost = 0;
    std::sort(graph.begin(), graph.end());
    DSU dsu(n);
    
    for (int i = 0; i < m; ++i) {
        int first_vertex = graph[i].second.first;
        int second_vertex = graph[i].second.second;
        int weight = graph[i].first;
        if (dsu.find(first_vertex) != dsu.find(second_vertex)) {
            cost += weight;
            dsu.merge(first_vertex, second_vertex);
        }
    }
    return cost;
}


int main(int argc, const char * argv[]) {
    int n = 0, m = 0;
    std::cin >> n >> m;
    std::vector<Edge> graph;
    
    for (int i = 0; i < m; ++i) {
        int b = 0, e = 0, w = 0;
        std::cin >> b >> e >> w;
        graph.push_back(std::make_pair(w, std::make_pair(--b, --e)));
    }
    

    std::cout << get_mst_size(n, m, graph) << std::endl;
    return 0;
}
