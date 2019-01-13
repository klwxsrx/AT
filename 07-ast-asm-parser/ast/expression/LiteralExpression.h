#pragma once
#include "IExpression.h"

class LiteralExpression : public IExpression {
public:
    explicit LiteralExpression(double value);
    void AcceptVisitor(IExpressionVisitor &visitor) const override;

private:
    double m_value;
};