#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <string>
#include <vector>
#include <map>
#include <nlohmann/json.hpp>

// Structure to represent layer details
struct LayerConfig {
    int layerIndex;
    std::string layerType;
    std::string inputFilePath;
    std::string outputFilePath;
    std::string weightsFilePath;
    std::string biasFilePath;
    std::map<std::string, std::vector<int>> attributes;
    std::string activation;
};

// JSON Parser class
class JsonParser {
public:
    // Constructor
    JsonParser(const std::string& filePath);

    // Parse JSON config and return a vector of layer configurations
    std::vector<LayerConfig> parseConfig() const;

private:
    std::string jsonFilePath;
};

#endif // JSON_PARSER_H
