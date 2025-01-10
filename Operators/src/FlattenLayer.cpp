#include "FlattenLayer.h"

void FlattenLayer::forward(float* input, size_t N, size_t C, size_t H, size_t W, float*& output) {
    // Total number of elements per sample
    size_t D = C * H * W;

    // Allocate memory for the output tensor (N * D elements)
    output = new float[N * D];

    // // Perform flattening
    // for (size_t n = 0; n < N; ++n) {
    //     for (size_t c = 0; c < C; ++c) {
    //         for (size_t h = 0; h < H; ++h) {
    //             for (size_t w = 0; w < W; ++w) {
    //                 // Calculate 1D indices for input and output
    //                 size_t inputIndex = ((n * C + c) * H + h) * W + w;
    //                 size_t outputIndex = n * D + (c * H * W + h * W + w);
    //                 output[outputIndex] = input[inputIndex];
    //             }
    //         }
    //     }
    // }

    for (size_t n = 0; n < N; ++n) {
        for (size_t d = 0; d < D; ++d) {
            size_t inputIndex = n * D + d; // 1D index for input
            size_t outputIndex = n * D + d; // 1D index for output
            output[outputIndex] = input[inputIndex]; // Copy input to output
        }
    }
}
