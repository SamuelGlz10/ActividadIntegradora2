#include <iostream>
#include "Kruskal.h"
#include "TravelingSalesman.h"
#include "FordFulkerson.h"
#include "LinealSearch.h"
using namespace std;


int main() {
    vector<int> arr = {2, 3, 4, 10, 40};
    int x = 10;
    int res = search(arr, x);
    if (res == -1)
       cout << "Not Present";
    else
       cout << "Present at Index " << res;
    return 0;
}   