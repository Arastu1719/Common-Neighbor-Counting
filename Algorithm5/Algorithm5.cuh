#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <iostream>
#include <vector>
#include <algorithm>

__global__ void MKernal(int* n, int *m, int *dev_offset, int *dev_dst, int *dev_cnt, int *dev_Threshold) {

    int u = blockIdx.x;
    int du = dev_offset[u + 1] - dev_offset[u];
    for (int p = dev_offset[u]; p < dev_offset[u + 1]; ++p) {
        int v = dev_dst[p];
        int dv = dev_offset[v + 1] - dev_offset[v];

        int c = 0, off1 = dev_offset[u], off2 = dev_offset[v], end1 = dev_offset[u + 1], end2 = dev_offset[v + 1];
        while (off1 < end1 && off2 < end2)
        {
            if (dev_dst[off1] < dev_dst[off2])
            {
                off1++;
            }
            else if (dev_dst[off1] > dev_dst[off2])
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
        dev_cnt[p] = c;
    }
}