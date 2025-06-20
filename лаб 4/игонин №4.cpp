#include <iostream>
#include <vector>
#include <climits>
#include <Windows.h>

using namespace std;

const int MAX_VERTICES  = 100;

struct Edge {
    int destination;
    int weight;
};

vector<vector<Edge>> graph(MAX_VERTICES);
vector<int> distances(MAX_VERTICES, INT_MAX);
vector<int> previous(MAX_VERTICES, -1);
vector<bool> visited(MAX_VERTICES, false);

void addEdge(int u, int v, int weight) {
    graph[u].push_back({ v, weight });
    graph[v].push_back({ u, weight });
}

void dijkstra(int start, int end) {
    distances[start] = 0;

    for (int i = 0; i < MAX_VERTICES; ++i) {
        int minDist = INT_MAX;
        int current = -1;

        for (int j = 0; j < MAX_VERTICES; ++j) {
            if (!visited[j] && distances[j] < minDist) {
                minDist = distances[j];
                current = j;
            }
        }

        if (current == -1) break;
        visited[current] = true;

        for (const Edge& edge : graph[current]) {
            int n = edge.destination;
            int newDist = distances[current] + edge.weight;

            if (newDist < distances[n]) {
                distances[n] = newDist;
                previous[n] = current;
            }
        }
    }

    if (distances[end] == INT_MAX) {
        cout << "Путь между вершинами не найден!" << endl;
        return;
    }

    vector<int> path;
    for (int at = end; at != -1; at = previous[at]) {
        path.push_back(at);
    }

    cout << "Кратчайший путь: ";
    for (int i = path.size() - 1; i >= 0; --i) {
        if (i != path.size() - 1) cout << " - ";
        cout << path[i];
    }
    cout << "\nВес пути: " << distances[end] << endl;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int vertices, edges;
    cout << "Введите количество вершин: ";
    cin >> vertices;
    cout << "Введите количество ребер: ";
    cin >> edges;

    cout << "Введите ребра вершина1 вершина2 вес:" << endl;
    for (int i = 0; i < edges; ++i) {
        int u, v, weight;
        cin >> u >> v >> weight;
        addEdge(u, v, weight);
    }

    int start, end;
    cout << "Введите начальную вершину: ";
    cin >> start;
    cout << "Введите конечную вершину: ";
    cin >> end;

    dijkstra(start, end);

    return 0;
}