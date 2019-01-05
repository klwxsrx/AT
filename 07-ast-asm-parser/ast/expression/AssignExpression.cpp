#include "AssignExpression.h"

AssignExpression::AssignExpression(std::string const& variableName, IExpression* expression)
    : m_variableName(variableName), m_expression(expression)
{
}

IExpression* AssignExpression::Left() const
{
    return nullptr;
}

IExpression* AssignExpression::Right() const
{
    return m_expression;
}

void AssignExpression::AcceptVisitor(IExpressionVisitor& visitor) const
{
    return visitor.Expression(IExpressionVisitor::Expression::Assign);
}