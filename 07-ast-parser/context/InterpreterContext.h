#pragma once
#include <map>
#include "IInterpreterContext.h"

class InterpeterContext : public IInterpreterContext {
public:
    void AssignVariable(std::string const &variableName, double value) override;
    double GetVariableValue(std::string const &variableName) const override;

private:
    std::map<std::string, double> m_variables;
};