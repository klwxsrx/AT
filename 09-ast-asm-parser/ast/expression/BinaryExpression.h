#pragma once
#include "IExpression.h"

class BinaryExpression : public IExpression {
public:
    enum struct Operation
    {
        Add,
        Sub,
        Mult,
        Div
    };

    BinaryExpression(IExpression* left, Operation operation, IExpression* right);
    void AcceptVisitor(IExpressionVisitor &visitor) const override;

private:
    IExpression* m_left;
    IExpression* m_right;
    Operation m_operation;
};