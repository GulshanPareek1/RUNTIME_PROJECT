// #ifndef BINARY_FILE_READER_H
// #define BINARY_FILE_READER_H

// #include <string>
// #include <vector>

// class BinaryFileReader {
// public:
//     // Constructor
//     BinaryFileReader(const std::string& filePath);

//     // Read data from binary file
//     std::vector<float> readData() const;

// private:
//     std::string binaryFilePath;
// };

// #endif // BINARY_FILE_READER_H

#ifndef BINARY_FILE_READER_H
#define BINARY_FILE_READER_H

#include <string>
#include <vector>

class BinaryFileReader {
public:
    // Constructor
    BinaryFileReader(const std::string& filePath);

    // Read data from binary file
    std::vector<float> readData() const;  // Renamed from readData

    // Write data to binary file
    void writeFile(const std::vector<float>& data) const;  // New method for writing data

private:
    std::string binaryFilePath;
};

#endif // BINARY_FILE_READER_H
