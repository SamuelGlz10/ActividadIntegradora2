#include <iostream>
#include <limits.h>
#include <queue>
#include <string.h>
using namespace std;

// Búsqueda en anchura para encontrar un camino aumentante
bool bfs(int** rGraph, int s, int t, int parent[], int N)
{
    bool visited[100];
    memset(visited, 0, sizeof(visited));
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < N; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                if (v == t) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return false;
}

// Algoritmo de Ford-Fulkerson para flujo máximo
int fordFulkerson(int graph[100][100], int s, int t, int N)
{
    int u, v;
    int rGraph[100][100];
    // Copia la capacidad original a la residual
    for (u = 0; u < N; u++)
        for (v = 0; v < N; v++)
            rGraph[u][v] = graph[u][v];
    int parent[100];
    int max_flow = 0;
    // Mientras exista un camino aumentante
    while (bfs((int**)rGraph, s, t, parent, N)) {
        int path_flow = INT_MAX;
        // Encuentra la capacidad mínima en el camino encontrado
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
        // Actualiza capacidades residuales
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
        max_flow += path_flow;
    }
    return max_flow;
}
