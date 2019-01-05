#pragma once
#include "IExpression.h"
#include "IExpressionNode.h"

class LiteralExpression : public IExpression, public IExpressionNode {
public:
    explicit LiteralExpression(double value);

    void AcceptVisitor(IExpressionVisitor &visitor) const override;
    IExpression *Left() const override;
    IExpression *Right() const override;

private:
    double m_value;
};