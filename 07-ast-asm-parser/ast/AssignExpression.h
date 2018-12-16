#pragma once
#include "IExpression.h"

class AssignExpression : public IExpression {
public:
    AssignExpression(std::string const& variableName, IExpression* expression);
    double Evaluate(IInterpreterContext &context) const override;

private:
    std::string m_variableName;
    IExpression* m_expression;
};