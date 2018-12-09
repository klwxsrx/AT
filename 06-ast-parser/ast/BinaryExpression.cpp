#include "BinaryExpression.h"

BinaryExpression::BinaryExpression(IExpression* left, Operation operation, IExpression* right)
    : m_left(left), m_operation(operation), m_right(right)
{
}

double BinaryExpression::Evaluate(IInterpreterContext &context) const
{
    switch (m_operation)
    {
        case Operation::Add:
            return m_left->Evaluate(context) + m_right->Evaluate(context);
        case Operation::Sub:
            return m_left->Evaluate(context) - m_right->Evaluate(context);
        case Operation::Mult:
            return m_left->Evaluate(context) * m_right->Evaluate(context);
        case Operation::Div:
            return m_left->Evaluate(context) / m_right->Evaluate(context);
    }
}