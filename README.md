# Neural Network Layer Execution and Testing Framework in C++

## Project Description

This project is a C++ framework designed to execute and test neural network layers such as Convolution, MaxPooling, and Linear layers.
 The framework leverages a JSON-based configuration file for defining layer properties and operations.
  It supports data processing, utility functions for binary file handling, parsing the json file
  and rigorous validation of output against reference files through a comprehensive testing suite.

## Tools and Libraries Used

    CMake: For project configuration and build management.

    NMake: Build tool for compiling and linking the project.

    nlohmann/json: A lightweight JSON library for parsing and handling configuration files.

    Visual Studio: Used as the primary IDE for development and debugging.

## Project Folder Structure

Project_Folder
├── Operators
│   ├── src
│   │   ├── ConvolutionLayer.cpp
│   │   ├── MaxPoolingLayer.cpp
│   │   ├── LinearLayer.cpp
│   ├── include
│   |   ├── ConvolutionLayer.h
│   |   ├── MaxPoolingLayer.h
│   |   ├── LinearLayer.h
|   ├── CMakeLists.txt
├── Test_Operators
│   ├── src
│   │   ├── Test_ConvolutionLayer.cpp
│   │   ├── Test_MaxPoolingLayer.cpp
│   │   ├── Test_LinearLayer.cpp
│   ├── include
│   |    ├── Test_ConvolutionLayer.h
│   |   ├── Test_MaxPoolingLayer.h
│   |   ├── Test_LinearLayer.h
|   ├── CMakeLists.txt
├── utilities
│   ├── src
│   │   ├── BinaryFileReader.cpp
│   │   ├── OutputComparer.cpp
|   |   |── JsonParser.cpp
│   ├── include
│   |   ├── BinaryFileReader.h
│   |   ├── OutputComparer.h
|   |   |── JsonParser.h
|   ├── CMakeLists.txt
├── data
│   ├── input
│   │   
│   ├── output
│   │   
│   ├── layer_dumps_binary
│       ├── layer_X_output_reference.bin
├── configs
│   ├── model_config.json
├── build
├── CMakeLists.txt
├── README.md
|──.gitignore

## Features

    Modular Layer Design: Each neural network layer is implemented as a separate class with encapsulated logic.

    JSON Configuration: Layers and parameters (e.g., kernel size, strides, weights, biases) are defined in an easy-to-edit JSON file.

    Binary File Handling: Efficient reading and writing of binary input/output files.

    Testing Framework: Automated tests to validate layer functionality against reference outputs.

    Custom Activations: Support for common activation functions like ReLU and Softmax.

## Step-by-Step Guide to Running the Project

    Step 1: Set Up the Environment

    Install the following tools:

    CMake (minimum version 3.15).

    Visual Studio with C++ development tools.

    NMake (provided with Visual Studio).

## Clone or download the project repository to your local system.

    git clone https://github.com/GulshanPareek1/RUNTIME_PROJECT
    cd <repository_folder>

    Step 2: Build the Project

    Create a build directory to store compiled files:

    mkdir build
    cd build

    Configure the project with CMake:

    cmake -G "NMake Makefiles" ..

    Compile the project using the following command:

    mingw32-make 

    Step 3: Run the Main Program

    Run the main program to execute neural network layers based on the configuration file:

    cd bin  (executable file is in build/bin folder)

    ./App

    Input: JSON configuration file (e.g., model_config.json).

    Output: Processed data saved in the layer_dumps_binary.

    Step 4: Run the Test Suite for every layer

    Execute the test program to validate layer outputs against given output files and generated otputs:

    ./Test_ConvolutionLayer

    Input: Binary input and reference files located in layer_dumps_binary.

    Output: Test results displayed on the console. Example:

    Test Passed: Outputs are matching for Convolution Layer!
    Test Passed: Outputs are matching for MaxPooling Layer!
    Test Passed: Outputs are matching for Linear Layer!

## Configuration File (JSON)

The JSON file defines the sequence and properties of layers to execute. Example:
```json
{
  "layers": [
    {
        "layer_index": 4,
        "layer_type": "Conv2d",
        "input": "layer_dumps_binary/layer_4_Conv2d_input.bin",
        "weights": "layer_dumps_binary/layer_4_Conv2d_weights.bin",
        "bias": "layer_dumps_binary/layer_4_Conv2d_bias.bin",
        "output": "layer_dumps_binary/layer_4_Conv2d_output.bin",
        "attributes": {
            "layer_type": "Conv2d",
            "kernel_size": [
                3,
                3
            ],
            "stride": [
                1,
                1
            ],
            "padding": [
                1,
                1
            ],
            "activation": "ReLU"
        }
    },
    {
        "layer_index": 5,
        "layer_type": "MaxPool2d",
        "input": "layer_dumps_binary/layer_5_MaxPool2d_input.bin",
        "weights": null,
        "bias": null,
        "output": "layer_dumps_binary/layer_5_MaxPool2d_output.bin",
        "attributes": {
            "layer_type": "MaxPool2d",
            "kernel_size": [
                2,
                2
            ],
            "stride": [
                2,
                2
            ]
        }
    },
    {
        "layer_index": 6,
        "layer_type": "Linear",
        "input": "layer_dumps_binary/layer_6_Linear_input.bin",
        "weights": "layer_dumps_binary/layer_6_Linear_weights.bin",
        "bias": "layer_dumps_binary/layer_6_Linear_bias.bin",
        "output": "layer_dumps_binary/layer_6_Linear_output.bin",
        "attributes": {
            "layer_type": "Linear",
            "activation": "ReLU"
        }
    }
  ]
}
```
## Example Layers

Convolution Layer

Reads input, weights, and biases from binary files.

Applies a convolution operation followed by an activation function (e.g., ReLU).

Outputs the result to a binary file and saves in reference file.

MaxPooling Layer

Performs down-sampling using the max pooling operation.

Takes kernel size and stride as parameters.

Linear Layer

Implements a fully connected layer.

Supports activation functions like ReLU and Softmax.

## Testing Framework

Each layer's functionality is validated using:

Input Files: Predefined input files for testing.

Reference Files: Expected output files for comparison.

OutputComparer: A utility to compare generated outputs against reference files.

Example Test Output

Test Passed: Outputs are matching for Convolution Layer!
Test Passed: Outputs are matching for MaxPooling Layer!
Test Passed: Outputs are matching for Linear Layer!

## Troubleshooting

Binary File Not Found:
Ensure the required files are present in the data/input directory and are named correctly.

CMake Configuration Error:
Verify that CMake is installed and added to your system's PATH.

Output Mismatch in Tests:
Check the layer implementation logic or reference files for consistency.




## Contributors
Gulshan Pareek


