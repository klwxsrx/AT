#pragma once
#include "IExpression.h"
#include "IExpressionNode.h"

class BinaryExpression : public IExpression, public IExpressionNode {
public:
    enum struct Operation
    {
        Add,
        Sub,
        Mult,
        Div,
    };

    BinaryExpression(IExpression* left, Operation operation, IExpression* right);

    IExpression *Left() const override;
    IExpression *Right() const override;
    void AcceptVisitor(IExpressionVisitor &visitor) const override;

private:
    IExpression* m_left;
    IExpression* m_right;
    Operation m_operation;
};