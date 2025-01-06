#include <string>
#include <vector>

class LinearLayer {
private:
    std::string inputFilePath;
    std::string weightsFilePath;
    std::string biasFilePath;
    std::string outputFilePath;
    std::string activation;

public:
    LinearLayer(
        const std::string& inputFilePath,
        const std::string& weightsFilePath,
        const std::string& biasFilePath,
        const std::string& outputFilePath,
        const std::string& activation
    );

    void execute();
};
