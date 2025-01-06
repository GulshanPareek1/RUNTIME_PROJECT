// #include "JsonParser.h"
// #include <fstream>
// #include <stdexcept>

// JsonParser::JsonParser(const std::string& filePath) : jsonFilePath(filePath) {}

// std::vector<LayerConfig> JsonParser::parseConfig() const {
//     std::ifstream file(jsonFilePath);
//     if (!file.is_open()) {
//         throw std::runtime_error("Unable to open JSON file: " + jsonFilePath);
//     }

//     nlohmann::json jsonData;
//     file >> jsonData;

//     std::vector<LayerConfig> layers;
//     for (const auto& layer : jsonData) {
//         LayerConfig config;

//         // Parsing basic fields
//         config.layerIndex = layer.at("layer_index").get<int>();
//         config.layerType = layer.at("layer_type").get<std::string>();
//         config.inputFilePath = layer.at("input").get<std::string>();
//         config.outputFilePath = layer.at("output").get<std::string>();

//         // Handling null or missing weights and bias paths
//         config.weightsFilePath = layer.value("weights", "");
//         config.biasFilePath = layer.value("bias", "");

//         // Parsing attributes
//         if (layer.contains("attributes")) {
//             for (const auto& attr : layer.at("attributes").items()) {
//                 if (attr.value().is_array()) {
//                     // Handling array attributes (e.g., kernel_size, stride)
//                     config.attributes[attr.key()] = attr.value().get<std::vector<int>>();
//                 } else if (attr.value().is_string()) {
//                     // Handle activation as string separately
//                     if (attr.key() == "activation") {
//                         config.activation = attr.value().get<std::string>();
//                     }
//                 } else if (attr.value().is_number()) {
//                     // If the attribute is a number, handle it as int
//                     config.attributes[attr.key()] = {attr.value().get<int>()};
//                 }
//             }
//         }

//         // Add the parsed layer configuration to the layers vector
//         layers.push_back(config);
//     }

//     return layers;
// }


// #include "JsonParser.h"
// #include <fstream>
// #include <stdexcept>

// JsonParser::JsonParser(const std::string& filePath) : jsonFilePath(filePath) {}

// std::vector<LayerConfig> JsonParser::parseConfig() const {
//     std::ifstream file(jsonFilePath);
//     if (!file.is_open()) {
//         throw std::runtime_error("Unable to open JSON file: " + jsonFilePath);
//     }

//     nlohmann::json jsonData;
//     file >> jsonData;

//     std::vector<LayerConfig> layers;
//     for (const auto& layer : jsonData) {
//         LayerConfig config;

//         // Parsing basic fields
//         config.layerIndex = layer.at("layer_index").get<int>();
//         config.layerType = layer.at("layer_type").get<std::string>();

//         // Handling null or missing input and output file paths
//         config.inputFilePath = (layer.contains("input") && !layer["input"].is_null()) ? layer.at("input").get<std::string>() : "";
//         config.outputFilePath = (layer.contains("output") && !layer["output"].is_null()) ? layer.at("output").get<std::string>() : "";

//         // Handling null or missing weights and bias paths
//         config.weightsFilePath = layer.value("weights", "");
//         config.biasFilePath = layer.value("bias", "");

//         // Parsing attributes
//         if (layer.contains("attributes")) {
//             for (const auto& attr : layer.at("attributes").items()) {
//                 if (attr.value().is_array()) {
//                     // Handling array attributes (e.g., kernel_size, stride)
//                     config.attributes[attr.key()] = attr.value().get<std::vector<int>>();
//                 } else if (attr.value().is_string()) {
//                     // Handle activation as string separately
//                     if (attr.key() == "activation") {
//                         config.activation = attr.value().get<std::string>();
//                     }
//                 } else if (attr.value().is_number()) {
//                     // If the attribute is a number, handle it as int
//                     config.attributes[attr.key()] = {attr.value().get<int>()};
//                 }
//             }
//         }

//         // Add the parsed layer configuration to the layers vector
//         layers.push_back(config);
//     }

//     return layers;
// }

#include "JsonParser.h"
#include <fstream>
#include <stdexcept>

JsonParser::JsonParser(const std::string& filePath) : jsonFilePath(filePath) {}

std::vector<LayerConfig> JsonParser::parseConfig() const {
    std::ifstream file(jsonFilePath);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open JSON file: " + jsonFilePath);
    }

    nlohmann::json jsonData;
    file >> jsonData;

    std::vector<LayerConfig> layers;
    for (const auto& layer : jsonData) {
        LayerConfig config;

        // Parsing basic fields with checks for null values
        config.layerIndex = layer.at("layer_index").get<int>();
        config.layerType = layer.at("layer_type").get<std::string>();

        // Handling null or missing 'input' and 'output' paths
        config.inputFilePath = layer.contains("input") && !layer["input"].is_null() ? layer["input"].get<std::string>() : "";
        config.outputFilePath = layer.contains("output") && !layer["output"].is_null() ? layer["output"].get<std::string>() : "";

        // Handling null or missing 'weights' and 'bias' fields
        config.weightsFilePath = layer.contains("weights") && !layer["weights"].is_null() ? layer["weights"].get<std::string>() : "";
        config.biasFilePath = layer.contains("bias") && !layer["bias"].is_null() ? layer["bias"].get<std::string>() : "";

        // Parsing attributes and ensuring proper type handling
        if (layer.contains("attributes")) {
            for (const auto& attr : layer["attributes"].items()) {
                if (attr.value().is_array()) {
                    // Handle array attributes (e.g., kernel_size, stride)
                    config.attributes[attr.key()] = attr.value().get<std::vector<int>>();
                } else if (attr.value().is_string()) {
                    // Handle activation as a string attribute
                    if (attr.key() == "activation") {
                        config.activation = attr.value().get<std::string>();
                    }
                } else if (attr.value().is_number()) {
                    // Handle numeric attributes (e.g., stride, padding)
                    config.attributes[attr.key()] = {attr.value().get<int>()};
                }
            }
        }

        // Add the parsed layer configuration to the layers vector
        layers.push_back(config);
    }

    return layers;
}
