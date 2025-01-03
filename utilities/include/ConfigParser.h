#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include <string>
#include <vector>
#include <map>
// #include <../../include/include/nlohmann/json.hpp>
#include<include/nlohmann/json.hpp>

struct LayerConfig {
    int layer_index;
    std::string layer_type;
    std::string input_file;
    std::string weights_file;
    std::string bias_file;
    std::string output_file;
    std::map<std::string, std::vector<int>> attributes; // e.g., kernel_size, stride, padding
    std::string activation;                             // Activation function
};

class ConfigParser {
public:
    ConfigParser(const std::string& configFilePath);
    std::vector<LayerConfig> parseConfig();

private:
    std::string configFilePath;
};

#endif // CONFIG_PARSER_H
