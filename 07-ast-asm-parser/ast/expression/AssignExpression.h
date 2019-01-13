#pragma once
#include "IExpression.h"
#include "../visitor/IExpressionVisitor.h"

class AssignExpression : public IExpression {
public:
    AssignExpression(std::string const& variableName, IExpression* expression);
    bool isFinalNode() const override;
    void AcceptVisitor(IExpressionVisitor &visitor) const override;

private:
    std::string m_variableName;
    IExpression* m_expression;
};