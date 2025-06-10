#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
#include <cmath>
#include "funciones\Kruskal.h"
#include "funciones\TravelingSalesman.h"
#include "funciones\FordFulkerson.h"
#include "funciones\LinealSearch.h"
using namespace std;

string idxToColony(int idx) {
    return string(1, 'A' + idx);
}

int main() {
    int N;
    cin >> N;

    // Leer matriz de distancias
    vector<vector<int>> dist(N, vector<int>(N));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            cin >> dist[i][j];

    // Leer matriz de capacidades
    vector<vector<int>> cap(N, vector<int>(N));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            cin >> cap[i][j];

    // Leer ubicaciones de centrales en formato (x,y)
    vector<pair<int, int>> centrales(N);
    string line;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar todo el buffer hasta el siguiente salto de línea real
    for (int i = 0; i < N; ++i) {
        do {
            getline(cin, line);
        } while (line.empty());
        int x, y;
        char p1, comma, p2;
        istringstream iss(line);
        iss >> p1 >> x >> comma >> y >> p2;
        centrales[i] = {x, y};
    }

    // 1. Kruskal: obtener aristas del MST
    vector<vector<int>> edges;
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            if (dist[i][j] > 0 && dist[i][j] < 1000000) {
                edges.push_back({i, j, dist[i][j]});
            }
        }
    }
    vector<pair<int, int>> mst_edges;
    sort(edges.begin(), edges.end(), comparator);
    DSU dsu(N);
    int count = 0;
    for (auto &e : edges) {
        int x = e[0], y = e[1], w = e[2];
        if (dsu.find(x) != dsu.find(y)) {
            dsu.unite(x, y);
            mst_edges.push_back({x, y});
            if (++count == N - 1) break;
        }
    }
    cout << "1." << endl;
    for (auto &arc : mst_edges) {
        cout << "(" << idxToColony(arc.first) << ", " << idxToColony(arc.second) << ")" << endl;
    }

    // 2. TSP: ruta óptima
    vector<int> path;
    int n = dist.size();
    vector<vector<int>> dp(1 << n, vector<int>(n, -1));
    vector<vector<int>> parent(1 << n, vector<int>(n, -1));
    function<int(int, int)> tsp_rec = [&](int mask, int pos) {
        if (mask == (1 << n) - 1) return dist[pos][0];
        if (dp[mask][pos] != -1) return dp[mask][pos];
        int ans = INT_MAX, best = -1;
        for (int i = 0; i < n; ++i) {
            if (!(mask & (1 << i))) {
                int cost = dist[pos][i] + tsp_rec(mask | (1 << i), i);
                if (cost < ans) {
                    ans = cost;
                    best = i;
                }
            }
        }
        parent[mask][pos] = best;
        return dp[mask][pos] = ans;
    };
    tsp_rec(1, 0);
    int mask = 1, pos = 0;
    path.push_back(0);
    while (true) {
        int nxt = parent[mask][pos];
        if (nxt == -1) break;
        path.push_back(nxt);
        mask |= (1 << nxt);
        pos = nxt;
    }
    path.push_back(0);
    cout << "2." << endl;
    for (size_t i = 0; i < path.size(); ++i) {
        cout << idxToColony(path[i]);
        if (i + 1 < path.size()) cout << " ";
    }
    cout << endl;

    // 3. Ford-Fulkerson
    int graph[100][100];
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            graph[i][j] = cap[i][j];
    int maxflow = fordFulkerson(graph, 0, N - 1, N);
    cout << "3." << endl;
    cout << maxflow << endl;

    // 4. Central más al este (mayor x)
    int idx_max_x = 0;
    for (int i = 1; i < N; ++i) {
        if (centrales[i].first > centrales[idx_max_x].first)
            idx_max_x = i;
    }
    cout << "4." << endl;
    cout << "(" << centrales[idx_max_x].first << ", " << centrales[idx_max_x].second << ")" << endl;

    return 0;
}