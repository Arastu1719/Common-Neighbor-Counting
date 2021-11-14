//#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
using namespace std;

class Graph
{
public:
    int n, m;
    vector<int> offset;
    vector<int> dst;
    vector<int> cnt;

    void printDST()
    {
        for (int i = 0; i < dst.size(); ++i)
            cout << dst[i] + 1 << ' ';
        cout << "\n";
    }

    void printOffset()
    {
        for (int i = 0; i < offset.size(); ++i)
            cout << offset[i] << ' ';
        cout << "\n";
    }

    void readGraph()
    {
        cin >> n >> m;
        cnt.resize(2 * m);
        vector<vector<int>> ed(n);
        offset.resize(n + 1);
        for (int i = 0; i < m; ++i)
        {
            int a, b;
            cin >> a >> b;
            // --a, --b;
            ed[a].push_back(b);
            ed[b].push_back(a);
        }
        for (int i = 0; i < n; ++i)
        {
            sort(ed[i].begin(), ed[i].end());
            dst.insert(dst.end(), ed[i].begin(), ed[i].end());
            if (i > 0)
            {
                offset[i] = offset[i - 1] + ed[i - 1].size();
            }
        }
        offset[n] = 2 * m;
    }
};
