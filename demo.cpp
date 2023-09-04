// Description: A demo of the NVML class
// nvcc demo.cpp nvml.cpp -o demo -lnvidia-ml
// ./demo
// LockGPUClocks needs priviledge to run
#include <iostream>
#include "nvml.hpp"

int main() {
    NVML nvml;
    printf("Graphics Clock: %d MHz\n", nvml.GetGraphicsClockMHz(0));
    printf("Memory Clock: %d MHz\n", nvml.GetMemoryClockMHz(0));
    printf("Power Usage: %.2lf W\n", nvml.GetPowerUsage(0) / 1000.0);
    // nvml.LockGPUClocks(0, 210, 1410);
    // printf("GPU clocks set to (gpuClkmin %d, gpuClkmax %d) for GPU %d\n", 210, 1410, 0);
    // printf("Graphics Clock: %d MHz\n", nvml.GetGraphicsClockMHz(0));
    // printf("Memory Clock: %d MHz\n", nvml.GetMemoryClockMHz(0));
    // printf("Power Usage: %.2lf W\n", nvml.GetPowerUsage(0) / 1000.0);
    return 0;
}