#include "JsonParser.h"
#include "BinaryFileReader.h"
#include "ConvolutionLayer.h"
#include "OutputComparer.h"
#include <iostream>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    try {
        JsonParser parser("../../configs/layer_config.json");
        std::vector<LayerConfig> config = parser.parseConfig();

        for (const auto& layer : config) {
            std::string layerType = layer.layerType;

            if (layerType == "Conv2d") {
                ConvolutionLayer convLayer(
                    layer.inputFilePath,
                    layer.weightsFilePath,
                    layer.biasFilePath,
                    layer.outputFilePath,  // Correct outputFilePath
                    layer.attributes.at("kernel_size"),
                    layer.attributes.at("stride"),
                    layer.attributes.at("padding"),
                    layer.activation
                );
                convLayer.execute();

                // Debugging: Print the file paths
                // std::cout << "Generated file path: " << layer.outputFilePath << std::endl;
                // std::cout << "Reference file path: " << layer.outputFilePath + "_reference.bin" << std::endl;

                // Check if the reference file exists before reading it
                std::string referenceFilePath = layer.outputFilePath + "_reference.bin";
                if (fs::exists(referenceFilePath)) {
                    BinaryFileReader generatedReader(layer.outputFilePath);
                    std::vector<float> generatedOutput = generatedReader.readData();

                    BinaryFileReader referenceReader(referenceFilePath);
                    std::vector<float> referenceOutput = referenceReader.readData();

                    // Compare the outputs
                    if (compareOutputs(generatedOutput, referenceOutput)) {
                        std::cout << "Test Passed: Outputs match!" << std::endl;
                    } else {
                        std::cerr << "Test Failed: Outputs do not match!" << std::endl;
                    }
                } else {
                    std::cerr << "Reference file does not exist: " << referenceFilePath << std::endl;
                }
            }
            // Add other layer types as needed
        }

        std::cout << "Execution complete!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}




