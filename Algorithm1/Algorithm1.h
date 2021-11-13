#include <bits/stdc++.h>
using namespace std;

extern const int Threshold = 2;

int intersectM(vector<int> &a1, vector<int> &a2)
{
    int c = 0, off1 = 0, off2 = 0, end1 = a1.size(), end2 = a2.size();
    while (off1 < end1 && off2 < end2)
    {
        if (a1[off1] < a2[off2])
        {
            off1++;
        }
        else if (a1[off1] > a2[off2])
        {
            off2++;
        }
        else
        {
            off1++;
            off2++;
            c++;
        }
    }
    return c;
}

int intersectPS(vector<int> &A1, vector<int> &A2)
{
    int c = 0;
    int off1 = 0;
    int off2 = 0;
    int end1 = A1.size();
    int end2 = A2.size();
    while (1)
    {
        off1 = lower_bound(A1.begin() + off1, A1.end(), A2[off2]) - A1.begin();
        if (off1 >= end1)
        {
            return c;
        }
        off2 = lower_bound(A2.begin() + off2, A2.end(), A1[off1]) - A2.begin();

        if (off2 >= end2)
        {
            return c;
        }
        if (A1[off1] == A2[off2])
        {
            off1 += 1;
            off2 += 1;
            c += 1;
            if (off1 >= end1 || off2 >= end2)
            {
                return c;
            }
        }
    }
    return c;
}

int intersectMPS(vector<int> &A, vector<int> &B)
{
    int du = A.size();
    int dv = B.size();
    if (du <= Threshold * dv && dv <= Threshold * du)
    {
        return intersectM(A, B);
    }
    return intersectPS(A, B);
}