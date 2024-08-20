#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <vector>
#include <functional>
#include <memory>
#include <string>

// Базовый класс для выполнения задач
class Executor {
public:
    virtual std::vector<int> run(const std::vector<int>& data, std::function<int(int)> fn) = 0;
    virtual ~Executor() = default;
};

// Фабрика для создания экземпляров исполнителей
class RunFactory {
public:
    static std::unique_ptr<Executor> create(const std::string& method);
};

#endif // EXECUTOR_H
