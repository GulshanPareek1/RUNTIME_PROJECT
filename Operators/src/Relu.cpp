#include "Relu.h"
#include <algorithm>  // for std::max
#include <iostream>
#include<vector>
// it's for flattened array 
void Relu::forward(const float* input , float* output , const std::vector<size_t>& shape)
{

    size_t N = shape[0];    // Batch size
    size_t C = shape[1];  // Channels
    size_t H = shape[2];  // Height 
    size_t W = shape[3];  // width 

    // Calculate the total number of elements
    size_t totalElements = N * C * H * W;

    for(size_t i =0;i<totalElements ;i++)
    {
        output[i] = std::max(0.0f , input[i]);
    }

    std::cout << "ReLU forward pass completed for input shape: [" << N << ", " << C << ", " << H << ", " << W << "]\n";
}