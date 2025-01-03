#ifndef CONV2D_LAYER_H
#define CONV2D_LAYER_H

#include <vector>
#include <iostream>

class Conv2DLayer {
public:
    Conv2DLayer(const std::vector<float>& weights, const std::vector<float>& bias, 
                int kernel_size, int stride, int padding);

    void forward(const std::vector<float>& input, std::vector<float>& output);

private:
    std::vector<float> weights;
    std::vector<float> bias;
    int kernel_size;
    int stride;
    int padding;
};

#endif // CONV2D_LAYER_H
