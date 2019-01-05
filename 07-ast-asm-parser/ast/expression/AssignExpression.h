#pragma once
#include "IExpression.h"
#include "IExpressionNode.h"

class AssignExpression : public IExpression, public IExpressionNode {
public:
    AssignExpression(std::string const& variableName, IExpression* expression);

    IExpression* Left() const override;
    IExpression* Right() const override;
    void AcceptVisitor(IExpressionVisitor& visitor) const override;

private:
    std::string m_variableName;
    IExpression* m_expression;
};