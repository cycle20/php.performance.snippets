#include <stdio.h>

#define CL_TARGET_OPENCL_VERSION 120
#include <CL/cl.h>

int main(void) {
    void getClInfo();

    getClInfo();

    return 0;
}

void getClInfo() {
    cl_platform_id * getClPlatforms(cl_uint *numberOfPlatforms);
    char * getClPlatformParam(cl_platform_id platform, cl_platform_info paramName);

    cl_platform_id* platformIds = NULL;
    cl_uint numPlatforms = 0;

    platformIds = getClPlatforms(&numPlatforms);
    fprintf(stderr, "Number of OpenCL Platforms: %i\n\n", numPlatforms);

    for (int platformIndex = 0; platformIndex < numPlatforms; platformIndex++) {

        cl_platform_id platform = platformIds[platformIndex];
        char *value = getClPlatformParam(platform, CL_PLATFORM_NAME);
        fprintf(stderr, "Platform Name: %s\n", value);
        free(value);

        value = getClPlatformParam(platform, CL_PLATFORM_VENDOR);
        fprintf(stderr, "    Vendor: %s\n", value);
        free(value);

        value = getClPlatformParam(platform, CL_PLATFORM_VERSION);
        fprintf(stderr, "    Version: %s\n", value);
        free(value);

        value = getClPlatformParam(platform, CL_PLATFORM_PROFILE);
        fprintf(stderr, "    Profile: %s\n", value);
        free(value);

        value = getClPlatformParam(platform, CL_PLATFORM_EXTENSIONS);
        fprintf(stderr, "    Extensions: %s\n", value);
        free(value);



        cl_device_id * getClGPUDevices(cl_platform_id platform, cl_uint *numDevices);
        cl_ulong getClDeviceParamULong(cl_device_id device, cl_device_info paramName);
        cl_uint getClDeviceParamUInt(cl_device_id device, cl_device_info paramName);
        size_t getClDeviceParamSizeT(cl_device_id device, cl_device_info paramName);
        char * getClDeviceParamChar(cl_device_id device, cl_device_info paramName);
        size_t * getClDeviceParamSizeTArray(cl_device_id device, cl_device_info paramName, cl_uint dimensions);

        cl_uint numDevices = 0;
        cl_device_id *devices = getClGPUDevices(platform, &numDevices);
        if (devices == NULL) {
            fprintf(stderr, "\n    GPU device not found\n");
            continue;
        }
        fprintf(stderr, "\n    Number of GPU Devices: %i\n", numDevices);

        for (int deviceIndex = 0; deviceIndex < numDevices; deviceIndex++) {
            cl_device_id device = devices[deviceIndex];

            char *charValue = getClDeviceParamChar(device, CL_DEVICE_NAME);
            fprintf(stderr, "        Device Name: %s\n", charValue);
            free(charValue);

            charValue = getClDeviceParamChar(device, CL_DRIVER_VERSION);
            fprintf(stderr, "        Driver Version: %s\n", charValue);
            free(charValue);

            cl_ulong longValue = getClDeviceParamULong(device, CL_DEVICE_MAX_MEM_ALLOC_SIZE);
            fprintf(stderr, "        Max Mem Alloc Size: %ld Bytes\n", longValue);

            longValue = getClDeviceParamULong(device, CL_DEVICE_LOCAL_MEM_SIZE);
            fprintf(stderr, "        Local Mem Size: %ld Bytes\n", longValue);

            cl_uint intValue = getClDeviceParamUInt(device, CL_DEVICE_MAX_COMPUTE_UNITS);
            fprintf(stderr, "        Max Compute Units: %d\n", intValue);

            size_t size = getClDeviceParamSizeT(device, CL_DEVICE_MAX_WORK_GROUP_SIZE);
            fprintf(stderr, "        Max Work Group Size: %ld\n", size);

            cl_uint maxDimensions = getClDeviceParamUInt(device, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS);
            fprintf(stderr, "        Max Work Item Dimensions: %d\n", maxDimensions);

            size_t *itemSizes = getClDeviceParamSizeTArray(device, CL_DEVICE_MAX_WORK_ITEM_SIZES, maxDimensions);
            for (int dimension = 0; dimension < maxDimensions; dimension++) {
                fprintf(stderr, "            Item Size of Dimension %d: %ld\n", dimension + 1, itemSizes[dimension]);
            }
            free(itemSizes);
        }

        free(devices);
    }

}

void clInit() {
    // TODO
}

cl_platform_id * getClPlatforms(cl_uint *numPlatforms) {
    cl_platform_id *platformIds = NULL;

    clGetPlatformIDs(0, NULL, numPlatforms);
    if (*numPlatforms == 0) {
        fprintf(stderr, "No OpenCL platforms found.");

        return NULL;
    }

    platformIds = malloc(sizeof(cl_platform_id) * *numPlatforms);
    clGetPlatformIDs(*numPlatforms, platformIds, NULL);

    return platformIds;
}

char * getClPlatformParam(cl_platform_id platform, cl_platform_info paramName) {
    size_t valueSize = 0;
    char *value = NULL;

    clGetPlatformInfo(platform, paramName, 0, NULL, &valueSize);
    value = calloc(valueSize + 1, sizeof(char));
    clGetPlatformInfo(platform, paramName, valueSize, value, NULL);

    return value;
}

cl_device_id * getClGPUDevices(cl_platform_id platform, cl_uint *numDevices) {
    cl_int result;

    result = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 0, NULL, numDevices);
    if (result == CL_DEVICE_NOT_FOUND) {
        return NULL;
    }


    cl_device_id *devices = malloc(sizeof(cl_device_id) * (*numDevices));
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, *numDevices, devices, NULL);

    return devices;
}

char * getClDeviceParamChar(cl_device_id device, cl_device_info paramName) {
    size_t valueSize = 0;
    char *value = NULL;

    clGetDeviceInfo(device, paramName, 0, NULL, &valueSize);
    value = calloc(valueSize + 1, sizeof(char));
    clGetDeviceInfo(device, paramName, valueSize, value, NULL);

    return value;
}

void getClDeviceParamNonTyped(cl_device_id device, cl_device_info paramName, void *result, size_t resultSize) {
    clGetDeviceInfo(device, paramName, resultSize, result, NULL);
}

cl_ulong getClDeviceParamULong(cl_device_id device, cl_device_info paramName) {
    cl_ulong result = 0;
    getClDeviceParamNonTyped(device, paramName, &result, sizeof(result));

    return result;
}

cl_uint getClDeviceParamUInt(cl_device_id device, cl_device_info paramName) {
    cl_uint result = 0;
    getClDeviceParamNonTyped(device, paramName, &result, sizeof(result));

    return result;
}

size_t getClDeviceParamSizeT(cl_device_id device, cl_device_info paramName) {
    size_t result = 0;
    getClDeviceParamNonTyped(device, paramName, &result, sizeof(result));

    return result;
}

size_t * getClDeviceParamSizeTArray(cl_device_id device, cl_device_info paramName, cl_uint dimensions) {
    size_t *result = calloc(dimensions, sizeof(size_t));
    getClDeviceParamNonTyped(device, paramName, result, dimensions * sizeof(size_t));

    return result;
}

// TODO: printPlatform
// TODO: printDevice
