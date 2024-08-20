#include <iostream>
#include "Executor.h"

int main() {
    std::vector<float> data = {1.0, 2.0, 3.0};
    auto function = [](float x) { return x * x; };

    try {
        auto executor = RunFactory::create("multi");
        auto result = executor->run(data, function);

        for (auto& value : result) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << std::endl;
    }

    return 0;
}
