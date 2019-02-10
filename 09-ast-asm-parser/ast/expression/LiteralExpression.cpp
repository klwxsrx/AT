#include "LiteralExpression.h"

LiteralExpression::LiteralExpression(double value)
    : m_value(value)
{
}

void LiteralExpression::AcceptVisitor(IExpressionVisitor &visitor) const {
    visitor.LiteralExpression(m_value);
}
