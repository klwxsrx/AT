#pragma once
#include "IExpression.h"

class VariableExpression : public IExpression {
public:
    explicit VariableExpression(std::string const& name);
    double Evaluate(IInterpreterContext &context) const override;

private:
    std::string m_variableName;
};