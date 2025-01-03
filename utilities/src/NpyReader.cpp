#include "../include/NpyReader.h"
// #include "NpyReader.h"
// #include <../../include/include/cnpy/cnpy.h>
#include<include/cnpy/cnpy.h>
#include <iostream>
#include <stdexcept>

std::vector<float> NpyReader::loadNpyFile(const std::string& filePath, std::vector<size_t>& shape) {
    cnpy::NpyArray npArray;

    try {
        npArray = cnpy::npy_load(filePath);
    } catch (const std::exception& e) {
        throw std::runtime_error("Error loading npy file: " + filePath + ", " + e.what());
    }

    shape = npArray.shape; // Save the shape of the loaded array
    float* dataPtr = npArray.data<float>();

    // Convert the raw data to a vector
    return std::vector<float>(dataPtr, dataPtr + npArray.num_vals);
}
