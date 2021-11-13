#include <bits/stdc++.h>
using namespace std;

int IntersectBMP(vector<bool> &B, vector<int> &A)
{
    int c = 0;
    for (int w : A)
    {
        if (B[w])
            c++;
    }
    return c;
}