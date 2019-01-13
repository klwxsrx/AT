#include "PrintVariableExpression.h"

PrintVariableExpression::PrintVariableExpression(std::string const& variableName)
    : m_variableName(variableName)
{
}

void PrintVariableExpression::AcceptVisitor(IExpressionVisitor &visitor) const {
    visitor.PrintExpression(m_variableName);
}
