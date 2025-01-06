#include "../include/JsonParser.h"
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
        config.layerIndex = layer.at("layer_index").get<int>();
        config.layerType = layer.at("layer_type").get<std::string>();
        config.inputFilePath = layer.at("input").get<std::string>();
        config.outputFilePath = layer.at("output").get<std::string>();
        config.weightsFilePath = layer.value("weights", "");
        config.biasFilePath = layer.value("bias", "");

        if (layer.contains("attributes")) {
            for (const auto& attr : layer.at("attributes").items()) {
                if (attr.value().is_array()) {
                    config.attributes[attr.key()] = attr.value().get<std::vector<int>>();
                }
            }
        }

        config.activation = layer.at("attributes").value("activation", "");

        layers.push_back(config);
    }

    return layers;
}
