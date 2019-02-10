#pragma once
#include <string>

class IInterpreterContext {
public:
    virtual void AssignVariable(std::string const& variableName, double value) = 0;
    virtual double GetVariableValue(std::string const& variableName) const = 0;
    virtual ~IInterpreterContext() = default;
};