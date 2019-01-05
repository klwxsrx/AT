#pragma once
#include "IExpression.h"
#include "IExpressionNode.h"

class PrintLiteralExpression : public IExpression, public IExpressionNode {
public:
    explicit PrintLiteralExpression(double value);

    void AcceptVisitor(IExpressionVisitor &visitor) const override;
    IExpression *Left() const override;
    IExpression *Right() const override;

private:
    double m_value;
};