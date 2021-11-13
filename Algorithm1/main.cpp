#include <bits/stdc++.h>
using namespace std;
#include "../Graph.h"
#include "Algorithm1.h"

int main()
{

    Graph g;
    g.readGraph();

    int p = 0, v;
    for (int i = 0; i < g.n; ++i) {
        while (p < g.offset[i + 1]) {
            vector<int> A, B;
            for (int j = g.offset[i]; j < g.offset[i + 1]; ++j) {
                A.push_back(g.dst[j]);
            }
            v = g.dst[p];
            for (int j = g.offset[v]; j < g.offset[v + 1]; ++j) {
                A.push_back(g.dst[j]);
            }
            g.cnt[i] = intersectMPS(A, B);
            cout << g.cnt[i] << "\n";
        }
    }

    return 0;
}