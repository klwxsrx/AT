#pragma once
#include "IExpression.h"

class AssignExpression : public IExpression {
public:
    AssignExpression(std::string const& variableName, Ptr && expression);
    double Evaluate(IInterpreterContext &context) const override;

private:
    std::string m_variableName;
    Ptr m_expression;
};