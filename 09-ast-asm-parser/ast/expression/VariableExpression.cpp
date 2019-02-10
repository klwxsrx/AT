#include "VariableExpression.h"

VariableExpression::VariableExpression(std::string const& name)
    : m_variableName(name)
{
}

void VariableExpression::AcceptVisitor(IExpressionVisitor &visitor) const {
    visitor.VariableExpression(m_variableName);
}


