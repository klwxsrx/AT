#pragma once
#include "IExpression.h"

class LiteralExpression : public IExpression
{
public:
    explicit LiteralExpression(double value);
    double Evaluate(IInterpreterContext &context) const override;

private:
    double m_value;
};