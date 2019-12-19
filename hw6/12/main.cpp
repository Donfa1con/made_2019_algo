/*
12. Мосты
Ребро неориентированного графа называется мостом,
если удаление этого ребра из графа увеличивает число компонент связности.
Дан неориентированный граф, требуется найти в нем все мосты.
Формат ввода
Первая строка входного файла содержит два целых
числа n и m — количество вершин и ребер графа соответственно (1 ≤ n ≤ 20000, 1 ≤ m ≤ 200000).
Следующие m строк содержат описание ребер по одному на строке.
Ребро номер i описывается двумя натуральными числами
bi, ei — номерами концов ребра (1 ≤ bi, ei ≤ n).
Формат вывода
Первая строка выходного файла должна содержать
одно натуральное число b — количество мостов в заданном графе.
На следующей строке выведите b целых чисел — номера ребер,
которые являются мостами, в возрастающем порядке.
Ребра нумеруются с единицы в том порядке, в котором они заданы во входном файле.

Пример
Ввод    Вывод
6 7       1
1 2       3
2 3
3 4
1 3
4 5
4 6
5 6
*/

#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <stack>


struct HashPair {
    template <class T1, class T2>
    size_t operator()(const std::pair<T1, T2>& p) const {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};


using Graph = std::vector<std::vector<int>>;
using Edge = std::pair<int, int>;
using Edges = std::unordered_map<Edge, std::pair<int, bool>, HashPair>;


void is_bridge(int cur_vertex, int to_vertex, const Edges& edges, std::set<int>& bridges) {
    int edge_id = 0;
    bool is_multiple = false;;
    auto edge = std::make_pair(cur_vertex, to_vertex);
    std::tie(edge_id, is_multiple) = edges.at(edge);
    if (!is_multiple) {
        bridges.insert(edge_id);
    }
}


void dfs(const Graph& graph, const Edges& edges, std::set<int>& bridges,
         std::stack<Edge>& stack, std::vector<int>& lowest, std::vector<int>& entry, int vertex) {
    int time = 0;
    int cur_vertex = 0, to_vertex = 0;
    stack.push(std::make_pair(vertex, vertex));
    while (!stack.empty()) {
        std::tie(cur_vertex, to_vertex) = stack.top();
        if (entry[cur_vertex] != -1) {
            if (lowest[cur_vertex] < lowest[to_vertex]) {
                lowest[to_vertex] = lowest[cur_vertex];
            } else if (lowest[cur_vertex] > entry[to_vertex]) {
                is_bridge(cur_vertex, to_vertex, edges, bridges);
            }
            stack.pop();
        } else {
            entry[cur_vertex] = lowest[cur_vertex] = time++;
            for (auto vertex: graph[cur_vertex]) {
                if (vertex != to_vertex) {
                    stack.push(std::make_pair(vertex, cur_vertex));
                }
            }
        }
    }
}


void find_bridges(const Graph& graph, const Edges& edges, std::set<int>& bridges) {
    std::stack<Edge> stack;
    std::vector<int> lowest(graph.size(), -1);
    std::vector<int> entry(graph.size(), -1);

    for (int vertex = 0; vertex < graph.size(); vertex++) {
        if (entry[vertex] == -1) {
            dfs(graph, edges, bridges, stack, lowest, entry, vertex);
        }
    }
}


int main() {
    std::ifstream input("bridges.in");
    std::ofstream output("bridges.out");
    
    int n = 0, m = 0;
    input >> n >> m;
    Graph graph(n);
    Edges edges;
    std::set<int> bridges;
    
    for (int edge_id = 0; edge_id < m; ++edge_id) {
        int b = 0, e = 0;
        input >> b >> e;
        --b; --e;
        graph[b].push_back(e);
        graph[e].push_back(b);
        
        Edge edge = std::make_pair(e, b);
        Edge rev_edge = std::make_pair(b, e);
        bool is_multiple = edges.count(edge);
        edges[edge] = std::make_pair(edge_id + 1, is_multiple);
        edges[rev_edge] = std::make_pair(edge_id + 1, is_multiple);
    }
    
    find_bridges(graph, edges, bridges);
    
    output << bridges.size() << std::endl;
    for (size_t bridge: bridges) {
        output << bridge << " ";
    }
}
