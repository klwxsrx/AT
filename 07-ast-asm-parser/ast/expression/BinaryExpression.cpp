#include "BinaryExpression.h"

BinaryExpression::BinaryExpression(IExpression* left, Operation operation, IExpression* right)
    : m_left(left), m_operation(operation), m_right(right)
{
}

IExpression *BinaryExpression::Left() const {
    return m_left;
}

IExpression *BinaryExpression::Right() const {
    return m_right;
}

void BinaryExpression::AcceptVisitor(IExpressionVisitor &visitor) const {
    switch (m_operation)
    {
        case Operation::Add:
            visitor.Expression(IExpressionVisitor::Expression::Add);
            break;
        case Operation::Sub:
            visitor.Expression(IExpressionVisitor::Expression::Sub);
            break;
        case Operation::Mult:
            visitor.Expression(IExpressionVisitor::Expression::Mult);
            break;
        case Operation::Div:
            visitor.Expression(IExpressionVisitor::Expression::Div);
            break;
        default:
            throw std::runtime_error("Unknown operation");
    }
}