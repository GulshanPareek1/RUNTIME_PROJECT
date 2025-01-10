#ifndef FLATTEN_LAYER_H
#define FLATTEN_LAYER_H

#include <cstddef>

class FlattenLayer {
public:
    // Forward function for the Flatten layer
    void forward(float* input, size_t N, size_t C, size_t H, size_t W, float*& output);

    
};

#endif // FLATTEN_LAYER_H
