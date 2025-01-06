#ifndef BINARY_FILE_READER_H
#define BINARY_FILE_READER_H

#include <string>
#include <vector>

class BinaryFileReader {
public:
    // Constructor
    BinaryFileReader(const std::string& filePath);

    // Read data from binary file
    std::vector<float> readData() const;

private:
    std::string binaryFilePath;
};

#endif // BINARY_FILE_READER_H
