#include <iostream>
#include <vector>
const long long int INFINITY = 10000000000000;
struct TEdge {
    unsigned long long  from;
    unsigned long long int to;
    long long int weight;
};
long long int BellmanFord(std::vector<TEdge>& graph,long long int n,long long int start,long long int finish) {
    std::vector<long long int> distances(n, INFINITY);
    distances[start] = 0;
    while(1) {
        bool flag = false;
        for (int i = 0; i < graph.size(); i++) {
            if (distances[graph[i].from - 1] < INFINITY) {
                if (distances[graph[i].to - 1] > distances[graph[i].from - 1] + graph[i].weight) {
                    distances[graph[i].to - 1] = distances[graph[i].from - 1] + graph[i].weight;
                    flag = true;
                }
            }
        }
        if (!flag) {
            break;
        }
    }
    return distances[finish];
}
int main() {
    std::cin.tie();
    std::ios_base::sync_with_stdio(false);
    std::vector<TEdge> graph;
    long long int n, m, start, finish  = 0;
    std::cin >> n >> m >> start >> finish;
    graph.resize(m);
    for (int i = 0; i < m; i++) {
        std::cin >> graph[i].from >> graph[i].to >> graph[i].weight;
    }
    long long int answer = BellmanFord(graph, n, start - 1, finish - 1);
    if (answer == INFINITY) {
        std::cout << "No solution" <<std::endl;
    } else {
        std::cout << answer << std::endl;
    }
    return 0;
}