#include "Executor.h"
#include <future>
#include <stdexcept>
#include <iostream>

// One-thread
class SingleThreadExecutor : public Executor {
public:
    std::vector<float> run(const std::vector<float>& data, std::function<float(float)> fn) override {
        std::vector<float> result;
        for (auto& item : data) {
            result.push_back(fn(item));
        }
        return result;
    }
};

// Multi-thread
class MultiThreadExecutor : public Executor {
public:
    std::vector<float> run(const std::vector<float>& data, std::function<float(float)> fn) override {
        std::vector<std::future<float>> futures;
        for (auto& item : data) {
            futures.push_back(std::async(std::launch::async, fn, item));
        }

        std::vector<float> result;
        for (auto& future : futures) {
            result.push_back(future.get());
        }
        return result;
    }
};

// OMP
class OMPExecutor : public Executor {
public:
    std::vector<float> run(const std::vector<float>& data, std::function<float(float)> fn) override {
        std::vector<float> results(data.size());
        #pragma omp parallel for
        for (size_t i = 0; i < data.size(); ++i) {
            results[i] = fn(data[i]);
        }
        return results;
    }
};

// Add your methods here
// ...

// Fabric method definition
std::unique_ptr<Executor> RunFactory::create(const std::string& method) {
    if (method == "single") {
        return std::make_unique<SingleThreadExecutor>();
    } else if (method == "multi") {
        return std::make_unique<MultiThreadExecutor>();
    } else if (method == "OMP") {
        return std::make_unique<OMPExecutor>();
    } else {
        // Add your methods here
        throw std::invalid_argument("Unknown method: " + method);
    }
}
