Neural Network Layer Execution and Testing Framework

Project Description

This project is a C++ framework designed to execute and test neural network layers such as Convolution, MaxPooling, and Linear layers. The framework leverages a JSON-based configuration file for defining layer properties and operations. It supports data processing, utility functions for binary file handling, and rigorous validation of output against reference files through a comprehensive testing suite.

Tools and Libraries Used

CMake: For project configuration and build management.

NMake: Build tool for compiling and linking the project.

nlohmann/json: A lightweight JSON library for parsing and handling configuration files.

Visual Studio: Used as the primary IDE for development and debugging.

Project Folder Structure

Project_Folder
├── Operators
│   ├── src
│   │   ├── ConvolutionLayer.cpp
│   │   ├── MaxPoolingLayer.cpp
│   │   ├── LinearLayer.cpp
│   ├── include
│       ├── ConvolutionLayer.h
│       ├── MaxPoolingLayer.h
│       ├── LinearLayer.h
├── Test_Operators
│   ├── src
│   │   ├── Test_ConvolutionLayer.cpp
│   │   ├── Test_MaxPoolingLayer.cpp
│   │   ├── Test_LinearLayer.cpp
│   ├── include
│       ├── Test_ConvolutionLayer.h
│       ├── Test_MaxPoolingLayer.h
│       ├── Test_LinearLayer.h
├── utilities
│   ├── src
│   │   ├── BinaryFileReader.cpp
│   │   ├── OutputComparer.cpp
│   ├── include
│       ├── BinaryFileReader.h
│       ├── OutputComparer.h
├── data
│   ├── input
│   │   ├── layer_X_input.bin
│   ├── output
│   │   ├── layer_X_output.bin
│   ├── reference
│       ├── layer_X_output_reference.bin
├── configs
│   ├── model_config.json
├── build
├── CMakeLists.txt
├── README.md

Features

Modular Layer Design: Each neural network layer is implemented as a separate class with encapsulated logic.

JSON Configuration: Layers and parameters (e.g., kernel size, strides, weights, biases) are defined in an easy-to-edit JSON file.

Binary File Handling: Efficient reading and writing of binary input/output files.

Testing Framework: Automated tests to validate layer functionality against reference outputs.

Custom Activations: Support for common activation functions like ReLU and Softmax.

Step-by-Step Guide to Running the Project

Step 1: Set Up the Environment

Install the following tools:

CMake (minimum version 3.15).

Visual Studio with C++ development tools.

NMake (provided with Visual Studio).

Clone or download the project repository to your local system.

git clone <repository_link>
cd <repository_folder>

Step 2: Build the Project

Create a build directory to store compiled files:

mkdir build
cd build

Configure the project with CMake:

cmake -G "NMake Makefiles" ..

Compile the project using the following command:

cmake --build .

Step 3: Run the Main Program

Run the main program to execute neural network layers based on the configuration file:

./main.exe ../configs/model_config.json

Input: JSON configuration file (e.g., model_config.json).

Output: Processed data saved in the data/output directory.

Step 4: Run the Test Suite

Execute the test program to validate layer outputs against reference files:

./Test_Operators.exe

Input: Binary input and reference files located in data/input and data/reference.

Output: Test results displayed on the console. Example:

Test Passed: Outputs are matching for Convolution Layer!
Test Passed: Outputs are matching for MaxPooling Layer!
Test Passed: Outputs are matching for Linear Layer!

Configuration File (JSON)

The JSON file defines the sequence and properties of layers to execute. Example:

{
  "layers": [
    {
      "type": "Convolution",
      "input_file": "data/input/layer_1_input.bin",
      "weights_file": "data/input/layer_1_weights.bin",
      "bias_file": "data/input/layer_1_bias.bin",
      "output_file": "data/output/layer_1_output.bin",
      "kernel_size": [3, 3],
      "stride": [1, 1],
      "activation": "ReLU"
    },
    {
      "type": "MaxPooling",
      "input_file": "data/output/layer_1_output.bin",
      "output_file": "data/output/layer_2_output.bin",
      "kernel_size": [2, 2],
      "stride": [2, 2]
    },
    {
      "type": "Linear",
      "input_file": "data/output/layer_2_output.bin",
      "weights_file": "data/input/layer_3_weights.bin",
      "bias_file": "data/input/layer_3_bias.bin",
      "output_file": "data/output/layer_3_output.bin",
      "activation": "Softmax"
    }
  ]
}

Example Layers

Convolution Layer

Reads input, weights, and biases from binary files.

Applies a convolution operation followed by an activation function (e.g., ReLU).

Outputs the result to a binary file.

MaxPooling Layer

Performs down-sampling using the max pooling operation.

Takes kernel size and stride as parameters.

Linear Layer

Implements a fully connected layer.

Supports activation functions like ReLU and Softmax.

Testing Framework

Each layer's functionality is validated using:

Input Files: Predefined input files for testing.

Reference Files: Expected output files for comparison.

OutputComparer: A utility to compare generated outputs against reference files.

Example Test Output

Test Passed: Outputs are matching for Convolution Layer!
Test Passed: Outputs are matching for MaxPooling Layer!
Test Passed: Outputs are matching for Linear Layer!

Troubleshooting

Binary File Not Found:
Ensure the required files are present in the data/input directory and are named correctly.

CMake Configuration Error:
Verify that CMake is installed and added to your system's PATH.

Output Mismatch in Tests:
Check the layer implementation logic or reference files for consistency.

Future Enhancements

Add support for more layers (e.g., Dropout, BatchNorm).

Optimize file reading/writing for large datasets.

Extend activation function support.

Enable multi-threaded execution for faster computation.

Contributors

[Your Name]

[Team Member Name(s)]

License

This project is licensed under the MIT License. See the LICENSE file for details.

