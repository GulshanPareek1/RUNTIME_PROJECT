#ifndef OUTPUTCOMPARER_H
#define OUTPUTCOMPARER_H

#include <vector>

bool compareOutputs(const std::vector<float>& generatedOutput, const std::vector<float>& referenceOutput, float margin = 1e-5);

#endif // OUTPUTCOMPARER_H
