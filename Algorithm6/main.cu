#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include "Graph.h"
#include "Algorithm3.cuh"
#include "Algorithm6.cuh"
int Threshold = 2;

int main() {

    Graph g;
    g.readGraph();

    int* dev_offset, * dev_dst, * dev_cnt, * dev_Threshold, * dev_n, * dev_m;
    bool* B;
    cudaMalloc((void**)&dev_offset, (g.n + 1) * sizeof(int));
    cudaMalloc((void**)&dev_dst, 2 * g.m * sizeof(int));
    cudaMalloc((void**)&dev_cnt, 2 * g.m * sizeof(int));
    cudaMalloc((void**)&dev_Threshold, sizeof(int));
    cudaMalloc((void**)&dev_n, sizeof(int));
    cudaMalloc((void**)&dev_m, sizeof(int));
    cudaMalloc((void**)&B, g.n * sizeof(bool));

    for (int i = 0; i <= g.n; ++i) {
        cudaMemcpy(&dev_offset[i], &g.offset[i], sizeof(int), cudaMemcpyHostToDevice);
        if (i < g.n) {
            bool temp = false;
            cudaMemcpy(&B[i], &temp, sizeof(bool), cudaMemcpyHostToDevice);
        }
    }

    for (int i = 0; i < 2 * g.m; ++i) {
        cudaMemcpy(&dev_dst[i], &g.dst[i], sizeof(int), cudaMemcpyHostToDevice);
    }
    cudaMemcpy(dev_Threshold, &Threshold, sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(dev_n, &g.n, sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(dev_m, &g.m, sizeof(int), cudaMemcpyHostToDevice);

    int p = sqrt(g.n);
    if (p * p < g.n) ++p;
    IntersectBMP << <p, 1, g.n * sizeof(bool)>> > (dev_n, dev_m, dev_offset, dev_dst, dev_cnt);
    cudaDeviceSynchronize();
    int* c = (int*)malloc(2 * g.m * sizeof(int));
    cudaMemcpy(c, dev_cnt, 2 * g.m * sizeof(int), cudaMemcpyDeviceToHost);
    for (int i = 0; i < 2 * g.m; ++i)
        printf("%d ", c[i]);

    return 0;
}