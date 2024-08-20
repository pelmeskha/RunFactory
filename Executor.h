#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <vector>
#include <functional>
#include <memory>
#include <string>

// Base Executor class
class Executor {
public:
    virtual std::vector<float> run(const std::vector<float>& data, std::function<float(float)> fn) = 0;
    virtual ~Executor() = default;
};

// Executor factory class
class RunFactory {
public:
    static std::unique_ptr<Executor> create(const std::string& method);
};

#endif // EXECUTOR_H
