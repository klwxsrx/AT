#include "PrintLiteralExpression.h"

PrintLiteralExpression::PrintLiteralExpression(double value)
    : m_value(value)
{
}

void PrintLiteralExpression::AcceptVisitor(IExpressionVisitor &visitor) const {
    visitor.LiteralExpression(m_value);
    visitor.Expression(IExpressionVisitor::Expression::PrintLiteral);
}

IExpression *PrintLiteralExpression::Left() const {
    return nullptr;
}

IExpression *PrintLiteralExpression::Right() const {
    return nullptr;
}
