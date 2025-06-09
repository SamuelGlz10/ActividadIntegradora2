#include <iostream>
#include "kruskal.h"
using namespace std;


int main() {
    vector<vector<int>> edges = {
        {0, 1, 10}, {1, 3, 15}, {2, 3, 4}, {2, 0, 6}, {0, 3, 5}
    };
    
    cout<<kruskalsMST(4, edges);
    
    return 0;
}   