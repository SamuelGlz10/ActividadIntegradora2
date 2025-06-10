#include <iostream>
#include <vector>
using namespace std;

// Búsqueda lineal en un vector
int search(vector<int>& arr, int x) {
    for (int i = 0; i < arr.size(); i++)
        if (arr[i] == x)
            return i;
    return -1;
}