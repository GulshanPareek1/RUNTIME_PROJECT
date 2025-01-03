#ifndef ACTIVATIONS_H
#define ACTIVATIONS_H

#include <vector>

class Activations {
public:
    // ReLU activation function
    static std::vector<float> relu(const std::vector<float>& input);
};

#endif // ACTIVATIONS_H
