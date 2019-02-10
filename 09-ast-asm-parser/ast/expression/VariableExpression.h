#pragma once
#include "IExpression.h"

class VariableExpression : public IExpression {
public:
    explicit VariableExpression(std::string const& name);
    void AcceptVisitor(IExpressionVisitor &visitor) const override;

private:
    std::string m_variableName;
};