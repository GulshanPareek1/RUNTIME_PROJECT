// #include "BinaryFileReader.h"
// #include <fstream>
// #include <stdexcept>
// #include <vector>
// #include <cstdint>

// BinaryFileReader::BinaryFileReader(const std::string& filePath) : binaryFilePath(filePath) {}

// std::vector<float> BinaryFileReader::readData() const {
//     std::ifstream file(binaryFilePath, std::ios::binary);
//     if (!file.is_open()) {
//         throw std::runtime_error("Unable to open binary file: " + binaryFilePath);
//     }

//     // Read dimensions
//     uint32_t numDimensions;
//     file.read(reinterpret_cast<char*>(&numDimensions), sizeof(uint32_t));

//     std::vector<uint32_t> dimensions(numDimensions);
//     file.read(reinterpret_cast<char*>(dimensions.data()), numDimensions * sizeof(uint32_t));

//     // Calculate total size
//     uint32_t totalSize = 1;
//     for (uint32_t dim : dimensions) {
//         totalSize *= dim;
//     }

//     // Read data
//     std::vector<float> data(totalSize);
//     file.read(reinterpret_cast<char*>(data.data()), totalSize * sizeof(float));

//     return data;
// }
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

void BinaryFileReader::writeFile(const std::vector<float>& data) const {
    std::ofstream file(binaryFilePath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open binary file for writing: " + binaryFilePath);
    }

    // For simplicity, we assume dimensions were already written in the same format as in readFile.
    // Write dimensions (for simplicity, assuming data dimensions are available, adjust as needed)
    uint32_t numDimensions = 3; // Example, should be based on your data
    file.write(reinterpret_cast<const char*>(&numDimensions), sizeof(uint32_t));

    std::vector<uint32_t> dimensions = { 1, 3, static_cast<uint32_t>(data.size()) }; // Example dims
    file.write(reinterpret_cast<const char*>(dimensions.data()), numDimensions * sizeof(uint32_t));

    // Write data
    file.write(reinterpret_cast<const char*>(data.data()), data.size() * sizeof(float));

    file.close();
}
