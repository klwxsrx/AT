#include "AssignExpression.h"

AssignExpression::AssignExpression(std::string const& variableName, IExpression* expression)
    : m_variableName(variableName), m_expression(expression)
{
}

bool AssignExpression::isFinalNode() const
{
    return false;
}

void AssignExpression::AcceptVisitor(IExpressionVisitor &visitor) const
{
    m_expression->AcceptVisitor(visitor);
    visitor.AssignExpression(m_variableName);
}