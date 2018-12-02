#include "LiteralExpression.h"

LiteralExpression::LiteralExpression(double value)
    : m_value(value)
{
}

double LiteralExpression::Evaluate(IInterpreterContext &context) const {
    return m_value;
}
