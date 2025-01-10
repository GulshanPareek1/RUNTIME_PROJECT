// will implement using the Google Test later once it's working 

#include <iostream>
#include <vector>
#include <cassert>
#include "Relu.h"
#include "BinaryFileReader.h"


void printTensor(const std::vector<float>& tensor, const std::vector<size_t>& shape) {
    size_t index = 0;
    std::cout << "Tensor (shape: ";
    for (size_t i = 0; i < shape.size(); ++i) {
        std::cout << shape[i] << (i == shape.size() - 1 ? ")" : " x ");
    }
    std::cout << "):\n";

    for (size_t c = 0; c < shape[1]; ++c) { // Iterate over channels
        std::cout << "Channel " << c + 1 << ":\n";
        for (size_t h = 0; h < shape[2]; ++h) {
            for (size_t w = 0; w < shape[3]; ++w) {
                std::cout << tensor[index++] << " ";
            }
            std::cout << "\n";
        }
    }
}


void testReluPractical()
{

    std::string inputFilePath = "layer_dumps_binary/layer_0_Conv2d_output.bin";
    BinaryFileReader reader(inputFilePath);
    // std::vector<float> input = reader.readData();  

    // shape of input tensor
    // std::vector<size_t> shape = {1 , 16 , 3 ,3};
    std::vector<size_t> shape = {1 , 2 , 3 ,3};  // channel = 2 are just for looking if the relu logic is working fine 

    // Input tensor (random data simulating output of previous convolutional layer)
    std::vector<float> input = {
        1.0f, -2.0f, 3.0f,  4.0f, -5.0f, 6.0f,  -7.0f, 8.0f, 9.0f,  // Channel 1
        0.0f, 2.0f, -3.0f, -4.0f, 5.0f,  6.0f,  7.0f,  8.0f, -9.0f,  // Channel 2
        // ... (14 more channels can be added as needed)
    };

    // output tensor 
    std::vector<float>output(input.size() , 0.0f);

    // Expected output after ReLU
    std::vector<float> expectedOutput = {
        1.0f, 0.0f, 3.0f,  4.0f, 0.0f, 6.0f,  0.0f, 8.0f, 9.0f,  // Channel 1
        0.0f, 2.0f, 0.0f,  0.0f, 5.0f, 6.0f,  7.0f, 8.0f, 0.0f,  // Channel 2
        // ... (14 more channels can be added as needed)
    };

    // creating a relu layer 
    Relu relu;

    // forward pass 
    relu.forward(input.data() , output.data() , shape);

    //  assert(output == expectedOutput)       // only availabe in debug mode 

    if(output!=expectedOutput)
    {
        throw std::runtime_error("Output doesn't match the expected output!");
    }

    std::cout << "ReLU test with practical data passed!\n";
    std::cout << "Input Tensor:\n";
    printTensor(input, shape);
    std::cout << "Output Tensor:\n";
    printTensor(output, shape);
}

// main function to run the test 
int main(){
    testReluPractical();
    return 0;
}