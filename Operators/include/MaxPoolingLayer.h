// #ifndef MAXPOOLINGLAYER_H
// #define MAXPOOLINGLAYER_H

// #include <vector>
// #include <string>

// class MaxPoolingLayer {
// public:
//     MaxPoolingLayer(
//         const std::string& inputFilePath,
//         const std::string& outputFilePath,
//         const std::vector<int>& kernelSize,
//         const std::vector<int>& stride
//     );
    
//     void execute();

// private:
//     std::string inputFilePath;
//     std::string outputFilePath;
//     std::vector<int> kernelSize;
//     std::vector<int> stride;
// };

// #endif // MAXPOOLINGLAYER_H


// Refactoring the code for excluding the file reading and writing operations from this file 

#ifndef MAXPOOLINGLAYER_H
#define MAXPOOLINGLAYER_H

#include <vector>

class MaxPoolingLayer {
public:
    MaxPoolingLayer(
        const std::vector<float>& inputData,
        int channels,
        int inputHeight,
        int inputWidth,
        const std::vector<int>& kernelSize,
        const std::vector<int>& stride
    );

    // Updated function signature matches main file
    std::vector<float> execute(int outputHeight, int outputWidth);

private:
    std::vector<float> inputData;
    int channels;
    int inputHeight;
    int inputWidth;
    std::vector<int> kernelSize;
    std::vector<int> stride;
};

#endif // MAXPOOLINGLAYER_H
