#ifndef CONVOLUTION_LAYER_H
#define CONVOLUTION_LAYER_H

#include <vector>
#include <string>

class ConvolutionLayer {
public:
    ConvolutionLayer(
        const std::string& inputFilePath,
        const std::string& weightsFilePath,
        const std::string& biasFilePath,
        const std::string& outputFilePath,
        const std::vector<int>& kernelSize,
        const std::vector<int>& stride,
        const std::vector<int>& padding,
        const std::string& activation);

    void execute(); // Perform the convolution operation

private:
    std::string inputFilePath;
    std::string weightsFilePath;
    std::string biasFilePath;
    std::string outputFilePath;
    std::vector<int> kernelSize;
    std::vector<int> stride;
    std::vector<int> padding;
    std::string activation;

    std::vector<float> applyActivation(const std::vector<float>& data) const;
    void applyPadding(std::vector<float>& input, int inputHeight, int inputWidth) const;
};

#endif // CONVOLUTION_LAYER_H
