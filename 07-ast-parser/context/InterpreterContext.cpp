#include "InterpreterContext.h"

void InterpeterContext::AssignVariable(std::string const &variableName, double value) {
    m_variables[variableName] = value;
}

double InterpeterContext::GetVariableValue(std::string const &variableName) const {
    auto it = m_variables.find(variableName);
    if (it == m_variables.end())
    {
        throw std::runtime_error("Variable not found");
    }
    return it->second;
}