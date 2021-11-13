#include <bits/stdc++.h>
using namespace std;
#include <omp.h>
#include "Algorithm4.h"

int main()
{
    Graph g;
    g.readGraph();
#pragma omp parallel for schedule(dynamic, g.m)
    for (int i = 0; i < g.dst.size(); ++i)
    {
        int v = g.dst[i];
        int u = FindSrc(g.offset, g.m, i);
        g.cnt[i] = ComputeCntBMP(g, u, v);
    }

    for (int i = 0; i < g.dst.size(); ++i)
    {
        int v = g.dst[i];
        int u = FindSrc(g.offset, g.m, i);
        cout << u + 1 << ' ' << v + 1 << ' ' << g.cnt[i] << "\n";
    }
    return 0;
}