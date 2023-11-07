#include <iostream>
#include <vector>
#include <stack>
#include <climits>

using namespace std;

struct Edge {
    int dest, weight;
};

void topologicalSort(vector<vector<Edge>> &graph, int V, int u, vector<bool> &visited, stack<int> &order) {
    visited[u] = true;

    for (const Edge &edge : graph[u]) {
        if (!visited[edge.dest]) {
            topologicalSort(graph, V, edge.dest, visited, order);
        }
    }

    order.push(u);
}

void shortestPathDAG(vector<vector<Edge>> &graph, int V, int src) {
    stack<int> order;
    vector<bool> visited(V, false);

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            topologicalSort(graph, V, i, visited, order);
        }
    }

    vector<int> distance(V, INT_MAX);
    distance[src] = 0;

    while (!order.empty()) {
        int u = order.top();
        order.pop();

        if (distance[u] != INT_MAX) {
            for (const Edge &edge : graph[u]) {
                int v = edge.dest;
                int w = edge.weight;

                if (distance[u] + w < distance[v]) {
                    distance[v] = distance[u] + w;
                }
            }
        }
    }

    cout << "Vertex\tDistance from Source" << endl;
    for (int i = 0; i < V; i++) {
        cout << i << "\t" << distance[i] << endl;
    }
}

int main() {
    int V, E;
    cout << "Enter the number of vertices and edges: ";
    cin >> V >> E;

    vector<vector<Edge>> graph(V);

    cout << "Enter source, destination, and weight for each edge:\n";
    for (int i = 0; i < E; i++) {
        int src, dest, weight;
        cin >> src >> dest >> weight;
        graph[src].push_back({dest, weight});
    }

    int source;
    cout << "Enter the source vertex: ";
    cin >> source;

    shortestPathDAG(graph, V, source);

    return 0;
}
