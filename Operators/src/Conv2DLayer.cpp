#include "Conv2DLayer.h"

Conv2DLayer::Conv2DLayer(const std::vector<float>& weights, const std::vector<float>& bias, 
                         int kernel_size, int stride, int padding)
    : weights(weights), bias(bias), kernel_size(kernel_size), stride(stride), padding(padding) {}

// Dummy forward function for now
void Conv2DLayer::forward(const std::vector<float>& input, std::vector<float>& output) {
    std::cout << "Performing dummy convolution..." << std::endl;

    // For testing, just copy input to output
    output = input;

    // Print some details for debugging
    std::cout << "Kernel Size: " << kernel_size << ", Stride: " << stride 
              << ", Padding: " << padding << std::endl;
    std::cout << "Input Size: " << input.size() << ", Output Size: " << output.size() << std::endl;
}
