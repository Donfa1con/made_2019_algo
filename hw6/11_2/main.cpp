/*
11_2. Количество различных путей
Дан невзвешенный неориентированный граф.
В графе может быть несколько кратчайших путей между какими-то вершинами.
Найдите количество различных кратчайших путей между заданными вершинами.
Требуемая сложность O(V+E).
Пример
Ввод    Вывод
 4        2
 5
 0 1
 0 2
 1 2
 1 3
 2 3
 
 0 3
*/
#include <iostream>
#include <vector>
#include <queue>
#include <limits>

size_t get_short_paths_count(const std::vector<std::vector<size_t>>& graph, size_t start, size_t end) {
    std::vector<size_t> paths_count(graph.size());
    size_t max_limit = std::numeric_limits<size_t>::max();
    std::vector<size_t> vertex_dist(graph.size());
    std::vector<bool> visited(graph.size());
    size_t distance = max_limit;
    std::queue<size_t> queue;
    
    queue.push(start);
    paths_count[start] = 1;
    visited[start] = true;
    
    while(!queue.empty()) {
        size_t cur_vertex = queue.front(); queue.pop();
        
        for (auto next_vertex: graph[cur_vertex]) {
            if (!visited[next_vertex]) {
                visited[next_vertex] = true;
                vertex_dist[next_vertex] = vertex_dist[cur_vertex] + 1;
                paths_count[next_vertex] = paths_count[cur_vertex];
                if (next_vertex == end) {
                    distance = vertex_dist[next_vertex];
                }
                if (vertex_dist[next_vertex] <= distance) {
                    queue.push(next_vertex);
                }
            } else if (vertex_dist[cur_vertex] < vertex_dist[next_vertex]) {
                paths_count[next_vertex] += paths_count[cur_vertex];
            }
        }
    }
    return paths_count[end];
}


int main(int argc, const char * argv[]) {
    size_t n_vertex = 0, n_edges = 0;
    
    std::cin >> n_vertex;
    std::cin >> n_edges;
    
    std::vector<std::vector<size_t>> graph(n_vertex);
    size_t u = 0, w = 0;
    for (size_t i = 0; i < n_edges; ++i) {
        std::cin >> u >> w;
        graph[u].push_back(w);
        graph[w].push_back(u);
    }
    
    std::cin >> u >> w;
    std::cout << get_short_paths_count(graph, u, w) << std::endl;
    return 0;
}
