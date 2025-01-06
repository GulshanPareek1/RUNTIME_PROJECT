
#include "JsonParser.h"
#include "BinaryFileReader.h"
#include "ConvolutionLayer.h"
#include "MaxPoolingLayer.h"
#include "OutputComparer.h"
#include "LinearLayer.h"
#include <iostream>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char** argv) {
    try {
        // Check if we are running tests
        bool runTests = false;
        if (argc > 1 && std::string(argv[1]) == "--test") {
            runTests = true;
        }

        if (runTests) {
            std::cout << "Running tests for Convolution Layer..." << std::endl;
            // Run tests here (you can add the code for testing)
        } else {
            // Running the main layer processing
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
                } else if (layerType == "MaxPool2d") {
                    MaxPoolingLayer maxPoolLayer(
                        layer.inputFilePath,
                        layer.outputFilePath,
                        layer.attributes.at("kernel_size"),
                        layer.attributes.at("stride")
                    );
                    maxPoolLayer.execute();
                    std::cout << "MaxPooling Layer is working Fine..!" << std::endl;
                } else if (layerType == "Linear") {
                    // Directly access activation as a string
                    // std::string activation = layer.attributes.at("activation");
                    // Directly assign activation as a string from the configuration
                    std::string activation = "";
                    // Directly access the activation attribute from the LayerConfig struct
                    if (!layer.activation.empty()) {
                        activation = layer.activation;  // Get the string stored in activation
                    } else {
                        // Handle the case where activation is not set (optional)
                        std::cerr << "Activation function not specified" << std::endl;
                    }
                    LinearLayer linearLayer(
                        layer.inputFilePath,
                        layer.weightsFilePath,
                        layer.biasFilePath,
                        layer.outputFilePath,
                        activation
                    );
                    linearLayer.execute();
                    std::cout << "Linear Layer execution complete!" << std::endl;
                }

                // Add other layer types as needed
            }

            std::cout << "Execution complete!" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
