#pragma once
#include "IExpression.h"
#include "IExpressionNode.h"

class VariableExpression : public IExpression, public IExpressionNode {
public:
    explicit VariableExpression(std::string const& name);

    void AcceptVisitor(IExpressionVisitor &visitor) const override;
    IExpression *Left() const override;
    IExpression *Right() const override;

private:
    std::string m_variableName;
};