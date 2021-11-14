#include <bits/stdc++.h>
using namespace std;
#include "../Graph.h"
#include "Algorithm1.h"

int main()
{
    Graph g;
    g.readGraph();

    auto start = std::chrono::high_resolution_clock::now();
    int p = 0, v;
    for (int i = 0; i < g.n; ++i)
    {
        while (p < g.offset[i + 1])
        {
            vector<int> A, B;
            for (int j = g.offset[i]; j < g.offset[i + 1]; ++j)
            {
                A.push_back(g.dst[j]);
            }
            v = g.dst[p];
            for (int j = g.offset[v]; j < g.offset[v + 1]; ++j)
            {
                B.push_back(g.dst[j]);
            }
            g.cnt[p] = intersectMPS(A, B);
            cout << g.cnt[p] << "\n";
            p++;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    int timeTaken = duration.count();
    cout << "time taken= " << timeTaken << " microseconds\n";

    return 0;
}
