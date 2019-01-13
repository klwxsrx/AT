#include "AssignExpression.h"

AssignExpression::AssignExpression(std::string const& variableName, IExpression* expression)
    : m_variableName(variableName), m_expression(expression)
{
}

void AssignExpression::AcceptVisitor(IExpressionVisitor &visitor) const
{
    m_expression->AcceptVisitor(visitor);
    visitor.AssignExpression(m_variableName);
}