#include "LinearLayer.h"
#include "BinaryFileReader.h"
#include "OutputComparer.h"
#include <iostream>

int main() {
    try {
        LinearLayer linearLayer(
            "layer_dumps_binary/layer_6_Linear_input.bin",
            "layer_dumps_binary/layer_6_Linear_weights.bin",
            "layer_dumps_binary/layer_6_Linear_bias.bin",
            "layer_dumps_binary/layer_6_Linear_output.bin",
            "ReLU"  // Example activation function
        );
        linearLayer.execute();

        // Compare the generated output with the reference
        std::string referenceFilePath = "layer_dumps_binary/layer_6_Linear_output.bin_reference.bin";
        BinaryFileReader generatedReader("layer_dumps_binary/layer_6_Linear_output.bin");
        std::vector<float> generatedOutput = generatedReader.readData();

        BinaryFileReader referenceReader(referenceFilePath);
        std::vector<float> referenceOutput = referenceReader.readData();

        if (compareOutputs(generatedOutput, referenceOutput)) {
            std::cout << "Test Passed: Outputs are matching for Linear Layer!" << std::endl;
        } else {
            std::cerr << "Test Failed: Outputs do not match!" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
