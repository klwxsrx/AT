#include "BinaryExpression.h"

BinaryExpression::BinaryExpression(Ptr && left, Operation operation, Ptr && right)
    : m_left(std::move(left)), m_operation(operation), m_right(std::move(right))
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