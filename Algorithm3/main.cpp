#include <bits/stdc++.h>
using namespace std;
#include <omp.h>
#include "Algorithm3.h"

int main()
{
    Graph g;
    g.readGraph();
    auto start = std::chrono::high_resolution_clock::now();
#pragma omp parallel for schedule(dynamic, g.m)
    for (int i = 0; i < g.dst.size(); ++i)
    {
        int v = g.dst[i];
        int u = FindSrc(g.offset, g.m, i);
        vector<int> A, B;
        for (int j = g.offset[u]; j < (u == g.n - 1 ? g.dst.size() : g.offset[u + 1]); ++j)
        {
            A.push_back(g.dst[j]);
        }
        for (int j = g.offset[v]; j < (v == g.n - 1 ? g.dst.size() : g.offset[v + 1]); ++j)
        {
            B.push_back(g.dst[j]);
        }
        g.cnt[i] = ComputeCntMPS(A, B);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    int timeTaken = duration.count();
    for (int i = 0; i < g.dst.size(); ++i)
    {
        int v = g.dst[i];
        int u = FindSrc(g.offset, g.m, i);
        cout << u + 1 << ' ' << v + 1 << ' ' << g.cnt[i] << "\n";
    }
    cout << "Time Taken=" << timeTaken << " microseconds" << endl;

    return 0;
}
