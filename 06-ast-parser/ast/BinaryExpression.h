#pragma once
#include "IExpression.h"

class BinaryExpression : public IExpression {
public:
    enum struct Operation
    {
        Add,
        Sub,
        Mult,
        Div,
    };

    BinaryExpression(Ptr && left, Operation operation, Ptr && right);
    double Evaluate(IInterpreterContext &context) const override;

private:
    Ptr m_left, m_right;
    Operation m_operation;
};