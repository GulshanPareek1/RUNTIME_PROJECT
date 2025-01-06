#include "ConvolutionLayer.h"
#include "BinaryFileReader.h"
#include "OutputComparer.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    try {
        std::string baseDir = "layer_dumps_binary/";

        // Define paths for input, weights, bias, and output files
        std::string inputFilePath = (fs::path(baseDir) / "layer_2_Conv2d_input.bin").string();
        std::string weightsFilePath = (fs::path(baseDir) / "layer_2_Conv2d_weights.bin").string();
        std::string biasFilePath = (fs::path(baseDir) / "layer_2_Conv2d_bias.bin").string();
        std::string outputFilePath = (fs::path(baseDir) / "layer_2_Conv2d_output.bin").string();
        std::string referenceFilePath = outputFilePath + "_reference.bin";

        // Ensure all required files exist before running the test
        if (!fs::exists(inputFilePath) || !fs::exists(weightsFilePath) || !fs::exists(biasFilePath)) {
            throw std::runtime_error("One or more required binary files are missing.");
        }

        ConvolutionLayer convLayer(inputFilePath, weightsFilePath, biasFilePath, outputFilePath, {3, 3}, {1, 1}, {1, 1}, "ReLU");
        convLayer.execute();

        // Check if reference file exists
        if (!fs::exists(referenceFilePath)) {
            throw std::runtime_error("Reference file does not exist: " + referenceFilePath);
        }

        BinaryFileReader generatedReader(outputFilePath);
        std::vector<float> generatedOutput = generatedReader.readData();

        BinaryFileReader referenceReader(referenceFilePath);
        std::vector<float> referenceOutput = referenceReader.readData();

        if (compareOutputs(generatedOutput, referenceOutput)) {
            std::cout << "Test Passed: Convolution Layer outputs match!" << std::endl;
        } else {
            std::cerr << "Test Failed: Convolution Layer outputs do not match!" << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
