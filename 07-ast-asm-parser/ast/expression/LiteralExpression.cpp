#include "LiteralExpression.h"

LiteralExpression::LiteralExpression(double value)
    : m_value(value)
{
}

void LiteralExpression::AcceptVisitor(IExpressionVisitor &visitor) const {
    visitor.LiteralExpression(m_value);
}

IExpression *LiteralExpression::Left() const {
    return nullptr;
}

IExpression *LiteralExpression::Right() const {
    return nullptr;
}
