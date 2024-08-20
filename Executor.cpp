#include "Executor.h"
#include <future>
#include <stdexcept>

// Однопоточное выполнение
class SingleThreadExecutor : public Executor {
public:
    std::vector<int> run(const std::vector<int>& data, std::function<int(int)> fn) override {
        std::vector<int> result;
        for (auto& item : data) {
            result.push_back(fn(item));
        }
        return result;
    }
};

// Многопоточное выполнение
class MultiThreadExecutor : public Executor {
public:
    std::vector<int> run(const std::vector<int>& data, std::function<int(int)> fn) override {
        std::vector<std::future<int>> futures;
        for (auto& item : data) {
            futures.push_back(std::async(std::launch::async, fn, item));
        }

        std::vector<int> result;
        for (auto& future : futures) {
            result.push_back(future.get());
        }
        return result;
    }
};

// Определение метода фабрики
std::unique_ptr<Executor> RunFactory::create(const std::string& method) {
    if (method == "single") {
        return std::make_unique<SingleThreadExecutor>();
    } else if (method == "multi") {
        return std::make_unique<MultiThreadExecutor>();
    } else {
        throw std::invalid_argument("Unknown method: " + method);
    }
}
