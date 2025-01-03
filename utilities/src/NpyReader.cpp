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

void NpyReader::testLoadNpyFile() {
    try {
        std::string testFilePath = "../../data/layer_dumps/layer_0_Conv2d_input.npy"; // Replace with the actual path to a test .npy file
        std::vector<size_t> shape;
        std::vector<float> data = loadNpyFile(testFilePath, shape);

        // Print out the shape and first few elements for verification
        std::cout << "Shape: ";
        for (size_t dim : shape) {
            std::cout << dim << " ";
        }
        std::cout << "\nData (first 5 elements): ";
        for (size_t i = 0; i < std::min(data.size(), size_t(5)); ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
    }
}
