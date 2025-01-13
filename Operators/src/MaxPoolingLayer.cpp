// #include "MaxPoolingLayer.h"
// #include "BinaryFileReader.h"
// #include <fstream>
// #include <stdexcept>
// #include <cmath>
// #include <iostream>

// MaxPoolingLayer::MaxPoolingLayer(
//     const std::string& inputFilePath,
//     const std::string& outputFilePath,
//     const std::vector<int>& kernelSize,
//     const std::vector<int>& stride
// )
//     : inputFilePath(inputFilePath),
//       outputFilePath(outputFilePath),
//       kernelSize(kernelSize),
//       stride(stride) {}

// void MaxPoolingLayer::execute() {
//     // Read input data
//     BinaryFileReader inputReader(inputFilePath);
//     std::vector<float> input = inputReader.readData();

//     // Assuming input shape is [channels, height, width]
//     int channels = input[0];
//     int inputHeight = input[1];
//     int inputWidth = input[2];
    
//     int outputHeight = (inputHeight - kernelSize[0]) / stride[0] + 1;
//     int outputWidth = (inputWidth - kernelSize[1]) / stride[1] + 1;

//     // Output vector
//     std::vector<float> output(outputHeight * outputWidth, 0.0f);

//     // Apply max pooling
//     for (int h = 0; h < outputHeight; ++h) {
//         for (int w = 0; w < outputWidth; ++w) {
//             float maxVal = -std::numeric_limits<float>::infinity();
//             for (int kh = 0; kh < kernelSize[0]; ++kh) {
//                 for (int kw = 0; kw < kernelSize[1]; ++kw) {
//                     int ih = h * stride[0] + kh;
//                     int iw = w * stride[1] + kw;

//                     if (ih < inputHeight && iw < inputWidth) {
//                         int inputIndex = ih * inputWidth + iw;
//                         maxVal = std::max(maxVal, input[inputIndex]);
//                     }
//                 }
//             }
//             output[h * outputWidth + w] = maxVal;
//         }
//     }

//     // Write output to binary file
//     std::ofstream outFile(outputFilePath, std::ios::binary);
//     if (!outFile) {
//         throw std::runtime_error("Unable to open output file for writing: " + outputFilePath);
//     }
//     outFile.write(reinterpret_cast<const char*>(output.data()), output.size() * sizeof(float));
//     outFile.close();

//     // Write reference output to a binary file
//     std::ofstream referenceFile(outputFilePath + "_reference.bin", std::ios::binary);
//     if (!referenceFile) {
//         throw std::runtime_error("Unable to open reference output file for writing: " + outputFilePath + "_reference.bin");
//     }
//     referenceFile.write(reinterpret_cast<const char*>(output.data()), output.size() * sizeof(float));
//     referenceFile.close();
// }



// Refactoring the code for excluding the file reading and writing operations from this file 

#include "MaxPoolingLayer.h"
#include <algorithm> // for std::max
#include <limits>    // for std::numeric_limits

MaxPoolingLayer::MaxPoolingLayer(
    const std::vector<float>& inputData,
    int channels,
    int inputHeight,
    int inputWidth,
    const std::vector<int>& kernelSize,
    const std::vector<int>& stride
)
    : inputData(inputData),
      channels(channels),
      inputHeight(inputHeight),
      inputWidth(inputWidth),
      kernelSize(kernelSize),
      stride(stride) {}

std::vector<float> MaxPoolingLayer::execute(int outputHeight, int outputWidth) {
    // Prepare output vector
    std::vector<float> output(channels * outputHeight * outputWidth, 0.0f);

    // Perform max pooling for each channel
    for (int c = 0; c < channels; ++c) {
        for (int h = 0; h < outputHeight; ++h) {
            for (int w = 0; w < outputWidth; ++w) {
                float maxVal = -std::numeric_limits<float>::infinity();

                for (int kh = 0; kh < kernelSize[0]; ++kh) {
                    for (int kw = 0; kw < kernelSize[1]; ++kw) {
                        int ih = h * stride[0] + kh;
                        int iw = w * stride[1] + kw;

                        if (ih < inputHeight && iw < inputWidth) {
                            int inputIndex = c * (inputHeight * inputWidth) + ih * inputWidth + iw;
                            maxVal = std::max(maxVal, inputData[inputIndex]);
                        }
                    }
                }

                int outputIndex = c * (outputHeight * outputWidth) + h * outputWidth + w;
                output[outputIndex] = maxVal;
            }
        }
    }

    return output; // Return the output
}
