#include "BinaryExpression.h"

BinaryExpression::BinaryExpression(IExpression* left, Operation operation, IExpression* right)
    : m_left(left), m_operation(operation), m_right(right)
{
}

void BinaryExpression::AcceptVisitor(IExpressionVisitor &visitor) const {
    m_left->AcceptVisitor(visitor);
    m_right->AcceptVisitor(visitor);

    switch (m_operation)
    {
        case Operation::Add:
            visitor.BinaryExpression(IExpressionVisitor::Expression::Add);
            break;
        case Operation::Sub:
            visitor.BinaryExpression(IExpressionVisitor::Expression::Sub);
            break;
        case Operation::Mult:
            visitor.BinaryExpression(IExpressionVisitor::Expression::Mult);
            break;
        case Operation::Div:
            visitor.BinaryExpression(IExpressionVisitor::Expression::Div);
            break;
        default:
            throw std::runtime_error("Unknown operation");
    }
}