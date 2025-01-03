#ifndef NPY_READER_H
#define NPY_READER_H

#include <string>
#include <vector>

class NpyReader {
public:
    static std::vector<float> loadNpyFile(const std::string& filePath, std::vector<size_t>& shape);

private:
    NpyReader() = default; // Prevent instantiation
};

#endif // NPY_READER_H
