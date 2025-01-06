#ifndef MAXPOOLINGLAYER_H
#define MAXPOOLINGLAYER_H

#include <vector>
#include <string>

class MaxPoolingLayer {
public:
    MaxPoolingLayer(
        const std::string& inputFilePath,
        const std::string& outputFilePath,
        const std::vector<int>& kernelSize,
        const std::vector<int>& stride
    );
    
    void execute();

private:
    std::string inputFilePath;
    std::string outputFilePath;
    std::vector<int> kernelSize;
    std::vector<int> stride;
};

#endif // MAXPOOLINGLAYER_H
