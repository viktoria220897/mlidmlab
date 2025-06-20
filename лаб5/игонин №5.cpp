#include <iostream>
using namespace std;

const int MAX_N = 100; // Максимальное количество вершин

class ReachabilityMatrix {
    int n; // Количество вершин
    int adj[MAX_N][MAX_N]; // Матрица смежности
    int reach[MAX_N][MAX_N]; // Матрица достижимости

public:
    // Инициализация графа
    ReachabilityMatrix(int vertices) : n(vertices) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                adj[i][j] = 0;
                reach[i][j] = 0;
            }
        }
    }

    // Добавление ребра от u к v
    void addEdge(int u, int v) {
        adj[u][v] = 1;
    }

    // Построение матрицы достижимости (алгоритм Уоршелла)
    void computeReachability() {
        // Инициализация матрицы достижимости
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                reach[i][j] = adj[i][j];
            }
            reach[i][i] = 1; // Вершина достижима из самой себя
        }

        // Алгоритм Уоршелла
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    reach[i][j] = reach[i][j] || (reach[i][k] && reach[k][j]);
                }
            }
        }
    }

    // Вывод матрицы достижимости
    void printMatrix() {
        cout << "Матрица достижимости:\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << reach[i][j] << " ";
            }
            cout << "\n";
        }
    }
};

int main() {
    int vertices, edges;

    cout << "Введите количество вершин графа: ";
    cin >> vertices;

    if (vertices <= 0 || vertices > MAX_N) {
        cout << "Некорректное количество вершин!\n";
        return 1;
    }

    ReachabilityMatrix graph(vertices);

    cout << "Введите количество ребер: ";
    cin >> edges;
    cout << "Введите ребра в формате 'u v' (0 <= u,v < " << vertices << "):\n";

    for (int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;
        if (u < 0 || u >= vertices || v < 0 || v >= vertices) {
            cout << "Некорректное ребро! Пропускаем.\n";
            continue;
        }
        graph.addEdge(u, v);
    }

    graph.computeReachability();
    graph.printMatrix();

    return 0;
}