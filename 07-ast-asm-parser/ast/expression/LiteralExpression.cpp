#include "LiteralExpression.h"

LiteralExpression::LiteralExpression(double value)
    : m_value(value)
{
}

bool LiteralExpression::isFinalNode() const
{
    return true;
}

void LiteralExpression::AcceptVisitor(IExpressionVisitor &visitor) const {
    visitor.LiteralExpression(m_value);
}
