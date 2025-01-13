
// #include "JsonParser.h"
// #include "BinaryFileReader.h"
// #include "ConvolutionLayer.h"
// #include "MaxPoolingLayer.h"
// #include "OutputComparer.h"
// #include "LinearLayer.h"
// #include <iostream>
// #include <vector>
// #include <filesystem>
// #include<chrono>   // for time measuring 

// namespace fs = std::filesystem;

// int main(int argc, char** argv) {
//     try {

//         // start the timer 
//         auto start = std::chrono::high_resolution_clock::now();

//         // Check if we are running tests
//         bool runTests = false;
//         if (argc > 1 && std::string(argv[1]) == "--test") {
//             runTests = true;
//         }

//         if (runTests) {
//             std::cout << "Running tests for Convolution Layer..." << std::endl;
//             // Run tests here (you can add the code for testing)
//         } else {
//             // Running the main layer processing
//             JsonParser parser("../../configs/layer_config.json");
//             std::vector<LayerConfig> config = parser.parseConfig();

//             for (const auto& layer : config) {
//                 std::string layerType = layer.layerType;

//                 /*read weight [0,1,2] and set as w_c, w_h, w_w
//                 create a memalloc of size (w_c, w_h, w_w)
//                 read the weights path to a file
//                 copy the weights binary to weights ptr

//                 */
//                 if (layerType == "Conv2d") {
//                     ConvolutionLayer convLayer(
//                         layer.inputFilePath,
//                         layer.weightsFilePath, //weight pointer along with w_c, w_h, w_w
//                         layer.biasFilePath,
//                         layer.outputFilePath,  // Correct outputFilePath
//                         layer.attributes.at("kernel_size"),
//                         layer.attributes.at("stride"),
//                         layer.attributes.at("padding"),
//                         layer.activation
//                     );
//                     convLayer.execute();
//                 } else if (layerType == "MaxPool2d") {
//                     MaxPoolingLayer maxPoolLayer(
//                         layer.inputFilePath,
//                         layer.outputFilePath,
//                         layer.attributes.at("kernel_size"),
//                         layer.attributes.at("stride")
//                     );
//                     maxPoolLayer.execute();
//                     std::cout << "MaxPooling Layer is working Fine..!" << std::endl;
//                 } else if (layerType == "Linear") {
//                     // Directly access activation as a string
//                     // std::string activation = layer.attributes.at("activation");
//                     // Directly assign activation as a string from the configuration
//                     std::string activation = "";
//                     // Directly access the activation attribute from the LayerConfig struct
//                     if (!layer.activation.empty()) {
//                         activation = layer.activation;  // Get the string stored in activation
//                     } else {
//                         // Handle the case where activation is not set (optional)
//                         std::cerr << "Activation function not specified" << std::endl;
//                     }
//                     LinearLayer linearLayer(
//                         layer.inputFilePath,
//                         layer.weightsFilePath,
//                         layer.biasFilePath,
//                         layer.outputFilePath,
//                         activation
//                     );
//                     linearLayer.execute();
//                     std::cout << "Linear Layer execution complete!" << std::endl;
//                 }

//                 // Add other layer types as needed
//             }

//             std::cout << "Execution complete!" << std::endl;
//         }
//         auto end = std::chrono::high_resolution_clock::now();
//         std::chrono::duration<double> elapsed = end-start;

//         std::cout<< "Total execution time: " << elapsed.count() << " seconds." <<std::endl;
//     } catch (const std::exception& e) {
//         std::cerr << "Error: " << e.what() << std::endl;
//         return EXIT_FAILURE;
//     }

//     return EXIT_SUCCESS;
// }



#include "JsonParser.h"
#include "BinaryFileReader.h"
#include "ConvolutionLayer.h"
#include "MaxPoolingLayer.h"
#include "OutputComparer.h"
#include "LinearLayer.h"
#include <iostream>
#include <vector>
#include <filesystem>
#include <chrono>   // for time measurement

namespace fs = std::filesystem;

int main(int argc, char** argv) {
    try {
        // Start the timer
        auto start = std::chrono::high_resolution_clock::now();

        // Check if we are running tests
        bool runTests = false;
        if (argc > 1 && std::string(argv[1]) == "--test") {
            runTests = true;
        }

        if (runTests) {
            std::cout << "Running tests for all layers..." << std::endl;
            // Add test logic if necessary
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
                        layer.outputFilePath,
                        layer.attributes.at("kernel_size"),
                        layer.attributes.at("stride"),
                        layer.attributes.at("padding"),
                        layer.activation
                    );
                    convLayer.execute();
                } else if (layer.layerType == "MaxPool2d") {
                // Read input data
                BinaryFileReader inputReader(layer.inputFilePath);
                std::vector<float> inputData = inputReader.readData();

                // Extract input dimensions
                std::vector<int> inputDims = layer.attributes.at("input_dims"); // [channels, height, width]
                int inputChannels = inputDims[0];
                int inputHeight = inputDims[1];
                int inputWidth = inputDims[2];

                // Get kernel size and stride
                std::vector<int> kernelSize = layer.attributes.at("kernel_size"); // [kernel_h, kernel_w]
                std::vector<int> stride = layer.attributes.at("stride");         // [stride_h, stride_w]

                // Calculate output dimensions
                int outputHeight = (inputHeight - kernelSize[0]) / stride[0] + 1;
                int outputWidth = (inputWidth - kernelSize[1]) / stride[1] + 1;

                // Instantiate MaxPoolingLayer
                MaxPoolingLayer maxPoolLayer(
                    inputData,
                    inputChannels,
                    inputHeight,
                    inputWidth,
                    kernelSize,
                    stride
                );

                // Execute max pooling and get output
                std::vector<float> outputData = maxPoolLayer.execute(outputHeight, outputWidth);

                // Write the output to a file
                BinaryFileReader outputWriter(layer.outputFilePath);
                outputWriter.writeFile(outputData);

                std::cout << "MaxPooling Layer executed successfully!" << std::endl;
            } else if (layerType == "Linear") {
                    std::string activation = "";
                    if (!layer.activation.empty()) {
                        activation = layer.activation;
                    } else {
                        std::cerr << "Activation function not specified for Linear Layer." << std::endl;
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

                // Handle additional layer types if needed
            }

            std::cout << "Execution complete!" << std::endl;
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Total execution time: " << elapsed.count() << " seconds." << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
