#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <iostream>
#include <vector>
#include <algorithm>

__global__ void IntersectBMP(int* n, int* m, int* dev_offset, int* dev_dst, int* dev_cnt)
{
    extern __shared__ bool B[];
    //n elements 8
    //    p = sqrt(n) bitmaps 2
    //    ceil(n / sqrt(n)) in each 3 blocks

    /*3 blocks
    1 bitmap per block
    0 1 | 2 3 | 4  5    p=(sqrt(6))=2 //  No blocks=3 //  
    0 1| 2 3 |4 5 | 6 7
    //0 1 2 | 3 4 5 | 6 7
*/
    
    /*3 blocks
    3 bitmaps-> size of each is N*/
    int l = 0, r = *n, mid;
    while (r > l + 1) {
        mid = (l + r) / 2;
        if (mid * mid <= *n) l = mid;
        else r = mid;
    }
    int p = l;
    //if (p * p < *n) p++;
    /*(0 1 2) * 3
        0, 3, 6*/
    int u = blockIdx.x * p;
    //printf("blockid = %d \n", blockIdx.x);
    int times = p;
    //bool B[*n];
    if (*n - u < p)
        times = *n - u;
    //printf("%d ", times);
    while (times--) {
        printf("u: %d ", u);
        int du = dev_offset[u + 1] - dev_offset[u];

        for (int j = dev_offset[u]; j < dev_offset[u + 1]; ++j) {
            B[dev_dst[j]] = true;
        }

        for (int j = dev_offset[u]; j < dev_offset[u + 1]; ++j) {
            int v = dev_dst[j];
            int c = 0;
            for (int k = dev_offset[v]; k < dev_offset[v + 1]; ++k) {
                if (B[dev_dst[k]]) {
                    c++;
                }
            }
            dev_cnt[j] = c;
        }

        for (int j = dev_offset[u]; j < dev_offset[u + 1]; ++j) {
            B[dev_dst[j]] = false;
        }

        ++u;
    }

    //int u = blockIdx.x;
}