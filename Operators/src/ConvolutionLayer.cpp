#include "ConvolutionLayer.h"
#include "BinaryFileReader.h"
#include <fstream>
#include <cmath>
#include <stdexcept>
#include<iostream>

ConvolutionLayer::ConvolutionLayer(
    const std::string& inputFilePath, 
    const std::string& weightsFilePath,//weight pointer along with w_c, w_h, w_w
    const std::string& biasFilePath,
    const std::string& outputFilePath,
    const std::vector<int>& kernelSize,
    const std::vector<int>& stride,
    const std::vector<int>& padding,
    const std::string& activation)
    : inputFilePath(inputFilePath),
      weightsFilePath(weightsFilePath),
      biasFilePath(biasFilePath),
      outputFilePath(outputFilePath),
      kernelSize(kernelSize),
      stride(stride),
      padding(padding),
      activation(activation) {}

void ConvolutionLayer::execute() {
    // Read input, weights, and bias
    BinaryFileReader inputReader(inputFilePath);
    BinaryFileReader weightsReader(weightsFilePath); //remove w
    BinaryFileReader biasReader(biasFilePath);

    std::vector<float> input = inputReader.readData();
    std::vector<float> weights = weightsReader.readData(); //remove w
    std::vector<float> bias = biasReader.readData();

    // Assume input shape is [channels, height, width]
    int channels = input[0];
    int inputHeight = input[1];
    int inputWidth = input[2];
    int outputHeight = ((inputHeight + 2 * padding[0] - kernelSize[0]) / stride[0]) + 1;
    int outputWidth = ((inputWidth + 2 * padding[1] - kernelSize[1]) / stride[1]) + 1;

    // Output vector
    std::vector<float> output(outputHeight * outputWidth, 0.0f);

    // Apply padding
    applyPadding(input, inputHeight, inputWidth);

    // Perform convolution
    for (int h = 0; h < outputHeight; ++h) { //size_t
        for (int w = 0; w < outputWidth; ++w) {
            float sum = 0.0f;

            for (int kh = 0; kh < kernelSize[0]; ++kh) {
                for (int kw = 0; kw < kernelSize[1]; ++kw) {
                    int ih = h * stride[0] + kh - padding[0];
                    int iw = w * stride[1] + kw - padding[1];

                    if (ih >= 0 && ih < inputHeight && iw >= 0 && iw < inputWidth) {
                        int inputIndex = ih * inputWidth + iw;
                        int weightIndex = kh * kernelSize[1] + kw;
                        sum += input[inputIndex] * weights[weightIndex];
                    }
                }
            }
            sum += bias[0]; // Assuming a single bias value per channel
            output[h * outputWidth + w] = sum;
        }
    }

    // Apply activation function
    output = applyActivation(output);

    // Write output to binary file
    std::ofstream outFile(outputFilePath, std::ios::binary);
    if (!outFile) {
        throw std::runtime_error("Unable to open output file for writing: " + outputFilePath);
    }
    outFile.write(reinterpret_cast<const char*>(output.data()), output.size() * sizeof(float));
    outFile.close();

    // Write reference output to a binary file
    std::ofstream referenceFile(outputFilePath + "_reference.bin", std::ios::binary);
    if (!referenceFile) {
        throw std::runtime_error("Unable to open reference output file for writing: " + outputFilePath + "_reference.bin");
    }
    referenceFile.write(reinterpret_cast<const char*>(output.data()), output.size() * sizeof(float));
    referenceFile.close();

    // Print paths for debugging
    std::cout << "Generated file path: " << outputFilePath << std::endl;
    std::cout << "Reference file path: " << outputFilePath + "_reference.bin" << std::endl;
}

std::vector<float> ConvolutionLayer::applyActivation(const std::vector<float>& data) const {
    std::vector<float> activatedData = data;

    if (activation == "ReLU") {
        for (float& val : activatedData) {
            val = std::max(0.0f, val);
        }
    }
    // Add other activation functions as needed

    return activatedData;
}

void ConvolutionLayer::applyPadding(std::vector<float>& input, int inputHeight, int inputWidth) const {
    if (padding[0] == 0 && padding[1] == 0) {
        return; // No padding required
    }

    int paddedHeight = inputHeight + 2 * padding[0];
    int paddedWidth = inputWidth + 2 * padding[1];
    std::vector<float> paddedInput(paddedHeight * paddedWidth, 0.0f);

    for (int h = 0; h < inputHeight; ++h) {
        for (int w = 0; w < inputWidth; ++w) {
            paddedInput[(h + padding[0]) * paddedWidth + (w + padding[1])] = input[h * inputWidth + w];
        }
    }

    input = paddedInput;
}
