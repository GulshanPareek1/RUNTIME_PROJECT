#include "LinearLayer.h"
#include "BinaryFileReader.h"
#include <fstream>
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <numeric>

LinearLayer::LinearLayer(
    const std::string& inputFilePath,
    const std::string& weightsFilePath,
    const std::string& biasFilePath,
    const std::string& outputFilePath,
    const std::string& activation
)
    : inputFilePath(inputFilePath),
      weightsFilePath(weightsFilePath),
      biasFilePath(biasFilePath),
      outputFilePath(outputFilePath),
      activation(activation) {}

void LinearLayer::execute() {
    // Read input, weights, and biases
    BinaryFileReader inputReader(inputFilePath);
    std::vector<float> input = inputReader.readData();

    BinaryFileReader weightsReader(weightsFilePath);
    std::vector<float> weights = weightsReader.readData();

    BinaryFileReader biasReader(biasFilePath);
    std::vector<float> biases = biasReader.readData();

    int numInputs = input.size();
    int numOutputs = biases.size();

    if (weights.size() != numInputs * numOutputs) {
        throw std::runtime_error("Mismatch in input size, output size, and weights dimensions.");
    }

    // Perform the linear operation: output = input * weights + bias
    std::vector<float> output(numOutputs, 0.0f);
    for (int j = 0; j < numOutputs; ++j) {
        for (int i = 0; i < numInputs; ++i) {
            output[j] += input[i] * weights[j * numInputs + i];
        }
        output[j] += biases[j];
    }

    // Apply activation function
    if (activation == "ReLU") {
        for (float& val : output) {
            val = std::max(0.0f, val);
        }
    } else if (activation == "Softmax") {
        // Apply Softmax
        float sumExp = 0.0f;
        for (float val : output) {
            sumExp += std::exp(val);
        }
        for (float& val : output) {
            val = std::exp(val) / sumExp;
        }
    } else {
        throw std::runtime_error("Unsupported activation function: " + activation);
    }

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
}
