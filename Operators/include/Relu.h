#ifndef RELU_H
#define RELU_H

#include <cstddef>  // for size_t
#include<vector>
class Relu{
    public:

    //constructor
    Relu() = default;

    void forward(const float* input , float* output , const std::vector<size_t>& shape);

    // destructor 
    ~Relu() = default;
};


#endif // RELU_H