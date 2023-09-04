#pragma once
#include <nvml.h>

// NVML Class
class NVML {
public:
    bool status = 0;
    unsigned int device_count;
    nvmlDevice_t devices[64];
    // Initialize NVML library
    void Init() {
        if (status) return;
        status = 1;
        nvmlReturn_t result;
        result = nvmlInit();
        if (NVML_SUCCESS != result) {
            printf("Failed to initialize NVML: %s\n", nvmlErrorString(result));
            exit(1);
        }
    }
    // Shutdown NVML library
    void Shutdown() {
        if (!status) return;
        status = 0;
        nvmlReturn_t result;
        result = nvmlShutdown();
        if (NVML_SUCCESS != result) {
            printf("Failed to shutdown NVML: %s\n", nvmlErrorString(result));
            exit(1);
        }
    }
    // Get device count
    void GetDeviceCount() {
        nvmlReturn_t result;
        result = nvmlDeviceGetCount(&device_count);
        if (NVML_SUCCESS != result) {
            printf("Failed to get device count: %s\n", nvmlErrorString(result));
            exit(1);
        }
        printf("Found %d device%s\n", device_count, device_count != 1 ? "s" : "");
    }
    // Get all device handle
    void GetDeviceHandle() {
        nvmlReturn_t result;
        for (int i = 0; i < device_count; i++) {
            result = nvmlDeviceGetHandleByIndex(i, &devices[i]);
            if (NVML_SUCCESS != result) {
                printf("Failed to get device %d handle: %s\n", i, nvmlErrorString(result));
                exit(1);
            }
        }
    }
    NVML() {
        Init();
        GetDeviceCount();
        GetDeviceHandle();
    }
    ~NVML() {
        Shutdown();
    }
    // Get device handle by index
    nvmlDevice_t GetDeviceHandleByIndex(int index) {
        return devices[index];
    }
    // Get graphics clock frequency
    unsigned int GetGraphicsClockMHz(int index) {
        nvmlReturn_t result;
        unsigned int graphicsClockMHz;
        nvmlClockType_t clockType;
        clockType = NVML_CLOCK_GRAPHICS;
        result = nvmlDeviceGetClockInfo(devices[index], clockType, &graphicsClockMHz);
        if (NVML_SUCCESS != result) {
            printf("Failed to get graphics clock frequency: %s\n", nvmlErrorString(result));
            return 0;
            // exit(1);
        }
        return graphicsClockMHz;
    }
    // Get memory clock frequency
    unsigned int GetMemoryClockMHz(int index) {
        nvmlReturn_t result;
        unsigned int memoryClockMHz;
        nvmlClockType_t clockType;
        clockType = NVML_CLOCK_MEM;
        result = nvmlDeviceGetClockInfo(devices[index], clockType, &memoryClockMHz);
        if (NVML_SUCCESS != result) {
            printf("Failed to get memory clock frequency: %s\n", nvmlErrorString(result));
            return 0;
            // exit(1);
        }
        return memoryClockMHz;
    }
    // Get utilization
    nvmlUtilization_t GetUtilization(int index) {
        nvmlReturn_t result;
        nvmlUtilization_t utilization;
        result = nvmlDeviceGetUtilizationRates(devices[index], &utilization);
        if (result != NVML_SUCCESS) {
            printf("Failed to get utilization rates: %s\n", nvmlErrorString(result));
            return nvmlUtilization_t{0, 0};
            // nvmlShutdown();
            // exit(1);
        }
        return utilization;
    }
    // Get SM utilization
    unsigned int GetSMUtilization(int index) {
        nvmlReturn_t result;
        nvmlUtilization_t utilization;
        result = nvmlDeviceGetUtilizationRates(devices[index], &utilization);
        if (result != NVML_SUCCESS) {
            printf("Failed to get utilization rates: %s\n", nvmlErrorString(result));
            return 0;
            // nvmlShutdown();
            // exit(1);
        }
        return utilization.gpu;
    }
    // Get memory utilization
    unsigned int GetMemoryUtilization(int index) {
        nvmlReturn_t result;
        nvmlUtilization_t utilization;
        result = nvmlDeviceGetUtilizationRates(devices[index], &utilization);
        if (result != NVML_SUCCESS) {
            printf("Failed to get utilization rates: %s\n", nvmlErrorString(result));
            return -1;
            // nvmlShutdown();
            // exit(1);
        }
        return utilization.memory;
    }
    // Get power usage
    unsigned int GetPowerUsage(int index) {
        nvmlReturn_t result;
        unsigned int powerUsage;
        result = nvmlDeviceGetPowerUsage(devices[index], &powerUsage);
        if (result != NVML_SUCCESS) {
            printf("Failed to get power usage: %s\n", nvmlErrorString(result));
            return 0;
            // nvmlShutdown();
            // exit(1);
        }
        return powerUsage;
    }

    // Set application clocks
    int SetApplicationsClocks(int index, unsigned int memoryClockMHz, unsigned int graphicsClockMHz) {
        nvmlReturn_t result;
        result = nvmlDeviceSetApplicationsClocks(devices[index], memoryClockMHz, graphicsClockMHz);
        if (NVML_SUCCESS != result)
        {
            printf("Failed to set application clocks: %s\n", nvmlErrorString(result));
            return 1;
        }
        return 0;
    }
    // Lock GPU clocks
    int LockGPUClocks(int index, unsigned int minGpuClockMHz, unsigned int maxGpuClockMHz) {
        nvmlReturn_t result;
        result = nvmlDeviceSetGpuLockedClocks(devices[index], minGpuClockMHz, maxGpuClockMHz);;
        if (NVML_SUCCESS != result)
        {
            printf("Failed to lock GPU clocks using LockGPUClocks: %s\n", nvmlErrorString(result));
            return 1;
        }
        return 0;
    }

};