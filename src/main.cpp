// // #include "ConfigParser.h"
// // #include <iostream>

// // int main() {
// //     // Use the real layer_configs.json file
// //     try{
// //         ConfigParser parser("../configs/json/layers.json");

// //     // Parse and display the configuration for each layer
// //     // auto config = parser.getConfig();
// //     auto config = parser.parseConfig();
// //     for (const auto& layer : config) {
// //         std::cout << "Layer Index: " << layer["layer_index"] << std::endl;
// //         std::cout << "Layer Type: " << layer["layer_type"] << std::endl;
// //         std::cout << "Input Path: " << layer["input"] << std::endl;
// //         std::cout << "Weights Path: " << layer["weights"] << std::endl;
// //         std::cout << "Bias Path: " << layer["bias"] << std::endl;
// //         std::cout << "Output Path: " << layer["output"] << std::endl;
// //         std::cout << "---------" << std::endl;
// //     }
// //     }
// //     catch (const std::exception& ex) {
// //         std::cerr << "Error: " << ex.what() << std::endl;
// //     }
    

// //     return 0;
// // }

// // #include "NpyReader.h"
// // #include <iostream>

// // int main() {
// //     NpyReader reader;

// //     // Example: Load and print data from a specific .npy file
// //     std::string inputPath = "layer_dumps/layer_0_Conv2d_input.npy";
// //     auto inputData = reader.loadNpyFile(inputPath);

// //     std::cout << "Data from " << inputPath << ": ";
// //     for (const auto& value : inputData) {
// //         std::cout << value << " ";
// //     }

// //     return 0;
// // }


// #include <iostream>
#include "NpyReader.h"
// #include "Conv2DLayer.h"
// #include <vector>
// #include <string>

// // Define a simple LayerConfig structure for simulation
// struct LayerConfig {
//     std::string layer_type;
//     std::string input_file;
//     std::string weights_file;
//     std::string bias_file;
//     int kernel_size;
//     int stride;
//     int padding;
// };

// void executeNetwork(const std::vector<LayerConfig>& configs) {
//     std::vector<float> input;

//     std::vector<size_t> input_shape;
//     // Load initial input from the first layer's input file
//     input = NpyReader::loadNpyFile(configs[0].input_file,input_shape);

//     for (const auto& config : configs) {
//         std::vector<float> output;

//         if (config.layer_type == "Conv2d") {
//             std::vector<size_t> shape; // Declare shape for each call
//             // Load weights and bias from files
//             auto weights = NpyReader::loadNpyFile(config.weights_file,shape);
//             auto bias = NpyReader::loadNpyFile(config.bias_file,shape);

//             // Create a Conv2DLayer
//             Conv2DLayer layer(weights, bias, config.kernel_size, config.stride, config.padding);

//             // Execute forward pass
//             layer.forward(input, output);
//         }

//         // Pass output to the next layer
//         input = output;
//     }

//     // Print final output size
//     std::cout << "Final output size: " << input.size() << std::endl;
//     std::cout << "Execution completed successfully!" << std::endl;
// }

// int main() {
//     try {
//         // Hardcoded configurations
//         std::vector<LayerConfig> configs = {
//             {"Conv2d", "layer_dumps/input.npy", "layer_dumps/weights.npy", "layer_dumps/bias.npy", 3, 1, 1},
//             // Add more layer configurations as needed
//         };

//         // Execute the network
//         executeNetwork(configs);
//     } catch (const std::exception& ex) {
//         std::cerr << "Error: " << ex.what() << std::endl;
//     }

//     return 0;
// }

#include <iostream>
#include "NpyReader.h"

int main(){
    std::cout<<"it's working.";
    NpyReader reader  ;
    reader.testLoadNpyFile();
    return 0;
}