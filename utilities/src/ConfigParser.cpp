// #include "../include/ConfigParser.h"
// #include <fstream>
// #include <iostream>

// using json = nlohmann::json;

// ConfigParser::ConfigParser(const std::string& configFilePath) : configFilePath(configFilePath) {}

// std::vector<LayerConfig> ConfigParser::parseConfig() {
//     std::vector<LayerConfig> layers;
//     std::ifstream configFile(configFilePath);

//     if (!configFile.is_open()) {
//         throw std::runtime_error("Could not open config file: " + configFilePath);
//     }

//     json configJson;
//     configFile >> configJson;

//     for (const auto& layer : configJson) {
//         LayerConfig layerConfig;

//         layerConfig.layer_index = layer.at("layer_index");
//         layerConfig.layer_type = layer.at("layer_type");
//         layerConfig.input_file = layer.at("input");
//         layerConfig.weights_file = layer.at("weights").is_null() ? "" : layer.at("weights");
//         layerConfig.bias_file = layer.at("bias").is_null() ? "" : layer.at("bias");
//         layerConfig.output_file = layer.at("output");

//         for (const auto& [key, value] : layer.at("attributes").items()) {
//             if (value.is_array()) {
//                 layerConfig.attributes[key] = value.get<std::vector<int>>();
//             }
//         }

//         if (layer.at("attributes").contains("activation")) {
//             layerConfig.activation = layer.at("attributes").at("activation");
//         } else {
//             layerConfig.activation = "";
//         }

//         layers.push_back(layerConfig);
//     }

//     return layers;
// }

#include "../include/ConfigParser.h"
#include <fstream>
#include <sstream>
#include <iostream>

ConfigParser::ConfigParser(const std::string& configFilePath) : configFilePath(configFilePath) {}

std::vector<LayerConfig> ConfigParser::parseConfig() {
    std::ifstream file(configFilePath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open config file: " + configFilePath);
    }

    // Parse the JSON file
    nlohmann::json jsonData;
    file >> jsonData;

    std::vector<LayerConfig> layers;

    for (const auto& layer : jsonData) {
        LayerConfig config;
        config.layer_index = layer["layer_index"];
        config.layer_type = layer["layer_type"];
        config.input_file = layer["input"];
        config.weights_file = layer["weights"].is_null() ? "" : layer["weights"];
        config.bias_file = layer["bias"].is_null() ? "" : layer["bias"];
        config.output_file = layer["output"];

        // Parse attributes
        if (layer.contains("attributes")) {
            for (const auto& [key, value] : layer["attributes"].items()) {
                config.attributes[key] = value.get<std::vector<int>>();
            }
        }

        // Parse activation (if present)
        if (layer["attributes"].contains("activation")) {
            config.activation = layer["attributes"]["activation"];
        } else {
            config.activation = "";
        }

        layers.push_back(config);
    }

    return layers;
}
