#include "FlattenLayer.h"
#include <iostream>
#include<chrono>   // for time measuring

// Function to print the output tensor
void printOutput(float* output, size_t N, size_t D) {
    for (size_t n = 0; n < N; ++n) {
        std::cout << "Batch " << n + 1 << ": ";
        for (size_t d = 0; d < D; ++d) {
            size_t index = n * D + d; // Calculate 1D index
            std::cout << output[index] << " ";
        }
        std::cout << std::endl;
    }
}

// Function to print the input tensor in multi-dimensional format
void printInput(float* input, size_t N, size_t C, size_t H, size_t W) {
    for (size_t n = 0; n < N; ++n) {
        std::cout << "Batch " << n + 1 << ":\n";
        for (size_t c = 0; c < C; ++c) {
            std::cout << "  Channel " << c + 1 << ":\n";
            for (size_t h = 0; h < H; ++h) {
                for (size_t w = 0; w < W; ++w) {
                    size_t index = ((n * C + c) * H + h) * W + w; // Calculate 1D index
                    std::cout << input[index] << " ";
                }
                std::cout << std::endl;
            }
        }
    }
}

int main() {
    // Input dimensions
    size_t N = 3; // Batch size
    size_t C = 3; // Channels
    size_t H = 3; // Height
    size_t W = 3; // Width

    // start the timer 
        auto start = std::chrono::high_resolution_clock::now();

    // Allocate memory for the input tensor (1D array)
    size_t totalInputElements = N * C * H * W;
    float* input = new float[totalInputElements];

    // Initialize input with test data
    float value = 1.0f;
    for (size_t i = 0; i < totalInputElements; ++i) {
        input[i] = value++;
    }

    // Print the input tensor
    std::cout << "Input Tensor:" << std::endl;
    printInput(input, N, C, H, W);

    // Flattened dimensions
    size_t D = C * H * W;
    float* output = nullptr;

    // Create FlattenLayer instance and perform forward pass
    FlattenLayer flattenLayer;
    flattenLayer.forward(input, N, C, H, W, output);

    // Print the output tensor
    std::cout << "\nFlattened Output Tensor:" << std::endl;
    printOutput(output, N, D);

    // Clean up memory
    delete[] input;
    delete[] output;

    auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end-start;

        std::cout<< "Total execution time: " << elapsed.count() << " seconds." <<std::endl;

    return 0;
}
