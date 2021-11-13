#include <bits/stdc++.h>
using namespace std;
#include "../Algorithm1/Algorithm1.h"
#include "../Algorithm2/Algorithm2.h"
#include "../Graph.h"

int FindSrc(const vector<int> &offset, int m, int pos)
{
    int n = offset.size();
    auto get_degree = [&](int i)
    {
        return (i == n - 1 ? m : offset[i + 1]) - offset[i];
    };
    static int u_tls = 0;
    static int count = 0;
    if (count == 2 * m)
    {
        u_tls = 0;
        count = 0;
    }
    if (pos >= offset[u_tls + 1])
    {
        u_tls = lower_bound(offset.begin() + u_tls + 1, offset.end(), pos) - offset.begin();
        if (offset[u_tls] > pos)
        {
            while (get_degree(u_tls - 1) == 0)
                u_tls--;
            u_tls--;
        }
        else
        {
            while (get_degree(u_tls) == 0)
                u_tls++;
        }
    }
    count++;
    return u_tls;
}

int ComputeCntBMP(const Graph &g, int u, int v)
{
    static int pu_tls = -1;
    static vector<bool> B_tls(g.n);

    if (u != pu_tls)
    {
        if (pu_tls != -1)
        {
            for (int j = g.offset[pu_tls]; j < (pu_tls == g.n - 1 ? g.dst.size() : g.offset[pu_tls + 1]); ++j)
            {
                B_tls[g.dst[j]] = false;
            }
        }
        for (int j = g.offset[u]; j < (u == g.n - 1 ? g.dst.size() : g.offset[u + 1]); ++j)
        {
            B_tls[g.dst[j]] = true;
        }
        pu_tls = u;
    }
    vector<int> A;
    for (int j = g.offset[v]; j < (v == g.n - 1 ? g.dst.size() : g.offset[v + 1]); ++j)
    {
        A.push_back(g.dst[j]);
    }
    return IntersectBMP(B_tls, A);
}