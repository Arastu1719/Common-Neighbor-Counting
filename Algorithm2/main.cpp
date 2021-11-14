#include <bits/stdc++.h>
using namespace std;
#include "../Graph.h"
#include "Algorithm2.h"
int main()
{
    Graph g;
    g.readGraph();
    auto start = std::chrono::high_resolution_clock::now();
    vector<bool> B(g.n);
    int v;

    int p = 0;
    for (int i = 0; i < g.n; ++i)
    {
        for (int j = g.offset[i]; j < g.offset[i + 1]; ++j)
        {
            B[g.dst[j]] = true;
        }

        while (p < g.offset[i + 1])
        {
            vector<int> A;
            v = g.dst[p];
            for (int k = g.offset[v]; k < g.offset[v + 1]; ++k)
            {
                A.push_back(g.dst[k]);
            }

            g.cnt[p] = IntersectBMP(B, A);
            ++p;
        }

        for (int j = g.offset[i]; j < (i == g.n - 1 ? g.dst.size() : g.offset[i + 1]); ++j)
        {
            B[g.dst[j]] = false;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    int timeTaken = duration.count();
    for (int i = 0; i < g.m; ++i)
    {
        cout << g.cnt[i] << "\n";
    }
    cout << "time taken= " << timeTaken << " microseconds\n";
    return 0;
}
