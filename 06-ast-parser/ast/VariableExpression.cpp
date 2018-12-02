#include "VariableExpression.h"

VariableExpression::VariableExpression(std::string const& name)
    : m_variableName(name)
{
}

double VariableExpression::Evaluate(IInterpreterContext &context) const {
    return context.GetVariableValue(m_variableName);
}
