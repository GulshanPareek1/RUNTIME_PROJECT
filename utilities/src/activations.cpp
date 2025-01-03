#include "../include/activations.h"
#include <algorithm>

std::vector<float> Activations::relu(const std::vector<float>& input) {
    std::vector<float> output(input.size());
    std::transform(input.begin(), input.end(), output.begin(), [](float x) {
        return std::max(0.0f, x);  // Apply ReLU
    });
    return output;
}
