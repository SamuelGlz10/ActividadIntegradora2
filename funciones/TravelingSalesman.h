#include <bits/stdc++.h>
using namespace std;

// Calcula el costo total mínimo usando programación dinámica y bitmask
int totalCost(int mask, int pos, int n, vector<vector<int>> &cost) {
    if (mask == (1 << n) - 1) {
        return cost[pos][0];
    }
    int ans = INT_MAX;
    for (int i = 0; i < n; i++) {
        if ((mask & (1 << i)) == 0) {
            ans = min(ans, cost[pos][i] + 
                      totalCost((mask | (1 << i)), i, n, cost));
        }
    }
    return ans;
}
// Wrapper para el problema del viajante
int tsp(vector<vector<int>> &cost) {
    int n = cost.size();
    return totalCost(1, 0, n, cost);  
}