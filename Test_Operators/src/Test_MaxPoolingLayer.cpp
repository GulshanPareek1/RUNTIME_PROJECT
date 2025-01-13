// #include "MaxPoolingLayer.h"
// #include "BinaryFileReader.h"
// #include "OutputComparer.h"
// #include <iostream>

// int main() {
//     try {
//         MaxPoolingLayer maxPoolLayer(
//             "layer_dumps_binary/layer_1_MaxPool2d_input.bin",
//             "layer_dumps_binary/layer_1_MaxPool2d_output.bin",
//             {2, 2},  // Kernel size
//             {2, 2}   // Stride
//         );
//         maxPoolLayer.execute();

//         // Compare the generated output with the reference
//         std::string referenceFilePath = "layer_dumps_binary/layer_1_MaxPool2d_output.bin_reference.bin";
//         BinaryFileReader generatedReader("layer_dumps_binary/layer_1_MaxPool2d_output.bin");
//         std::vector<float> generatedOutput = generatedReader.readData();

//         BinaryFileReader referenceReader(referenceFilePath);
//         std::vector<float> referenceOutput = referenceReader.readData();

//         if (compareOutputs(generatedOutput, referenceOutput)) {
//             std::cout << "Test Passed: Outputs are matching for MaxPooling Layer!" << std::endl;
//         } else {
//             std::cerr << "Test Failed: Outputs do not match!" << std::endl;
//         }
//     } catch (const std::exception& e) {
//         std::cerr << "Error: " << e.what() << std::endl;
//     }

//     return 0;
// }


#include "MaxPoolingLayer.h"
#include <iostream>
#include <cassert>

void testMaxPoolingLayer() {
    // Define the input data
    std::vector<float> inputData = {
        1, 2, 3, 4, 5, 6, 7, 8, 9, // Channel 0
        10, 11, 12, 13, 14, 15, 16, 17, 18, // Channel 1
        19, 20, 21, 22, 23, 24, 25, 26, 27  // Channel 2
    };

    int channels = 3;
    int inputHeight = 3;
    int inputWidth = 3;

    std::vector<int> kernelSize = {2, 2};
    std::vector<int> stride = {1, 1};

    // Calculate output dimensions
    int outputHeight = (inputHeight - kernelSize[0]) / stride[0] + 1;
    int outputWidth = (inputWidth - kernelSize[1]) / stride[1] + 1;

    // Create MaxPoolingLayer instance
    MaxPoolingLayer maxPoolingLayer(inputData, channels, inputHeight, inputWidth, kernelSize, stride);

    // Execute max pooling operation
    std::vector<float> output = maxPoolingLayer.execute(outputHeight, outputWidth);
    
    std::cout << "Output: ";
    for (float val : output) {
        std::cout << val << " ";
    }
    std::cout << std::endl;


    // Expected output after max pooling (with kernel size 2x2, stride 2x2)
    std::vector<float> expectedOutput = {
        5, 6,   // Channel 0
        8, 9,   // Channel 0
        14, 15, // Channel 1
        17, 18, // Channel 1
        23, 24, // Channel 2
        26, 27  // Channel 2
    };

    // Verify that the output matches the expected output
    assert(output == expectedOutput);   // assert only works in debug mode , in release mode it bypasses without checking 
    if(output!=expectedOutput)
    {
        throw std::runtime_error("Output doesn't match the expected output!  for MAXPOOLING LAYER");
    }

    std::cout << "MaxPoolingLayer test passed!   , actually the inputs we passed are generating an output which is matching with the expected outputs" << std::endl;
}

int main() {
    testMaxPoolingLayer();
    return 0;
}
