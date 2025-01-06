#include "BinaryFileReader.h"
#include <fstream>
#include <stdexcept>
#include <vector>
#include <cstdint>

BinaryFileReader::BinaryFileReader(const std::string& filePath) : binaryFilePath(filePath) {}

std::vector<float> BinaryFileReader::readData() const {
    std::ifstream file(binaryFilePath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open binary file: " + binaryFilePath);
    }

    // Read dimensions
    uint32_t numDimensions;
    file.read(reinterpret_cast<char*>(&numDimensions), sizeof(uint32_t));

    std::vector<uint32_t> dimensions(numDimensions);
    file.read(reinterpret_cast<char*>(dimensions.data()), numDimensions * sizeof(uint32_t));

    // Calculate total size
    uint32_t totalSize = 1;
    for (uint32_t dim : dimensions) {
        totalSize *= dim;
    }

    // Read data
    std::vector<float> data(totalSize);
    file.read(reinterpret_cast<char*>(data.data()), totalSize * sizeof(float));

    return data;
}
