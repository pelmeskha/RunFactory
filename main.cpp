#include <iostream>
#include "Executor.h"

int main() {
    std::vector<int> data = {1, 2, 3};
    auto calc = [](int x) { return x * x; };

    try {
        // Использование многопоточного выполнения
        auto executor = RunFactory::create("multi");
        auto result = executor->run(data, calc);

        for (auto& val : result) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
