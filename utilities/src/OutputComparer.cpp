#include "OutputComparer.h"
#include <cmath>
#include <iostream>

bool compareOutputs(const std::vector<float>& generatedOutput, const std::vector<float>& referenceOutput, float margin) {
    if (generatedOutput.size() != referenceOutput.size()) {
        std::cerr << "Error: Output sizes do not match!" << std::endl;
        return false;
    }

    for (size_t i = 0; i < generatedOutput.size(); ++i) {
        if (std::fabs(generatedOutput[i] - referenceOutput[i]) > margin) {
            std::cerr << "Mismatch at index " << i << ": Expected " << referenceOutput[i] << " but got " << generatedOutput[i] << std::endl;
            return false;
        }
    }

    return true;
}
