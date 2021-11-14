#include <bits/stdc++.h>
using namespace std;
#include <omp.h>
#include "Algorithm4.h"

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
        g.cnt[i] = ComputeCntBMP(g, u, v);
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
