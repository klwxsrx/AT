#pragma once
#include "IExpression.h"

class PrintVariableExpression : public IExpression {
public:
    explicit PrintVariableExpression(std::string const& variableName);
    void AcceptVisitor(IExpressionVisitor &visitor) const override;

private:
    std::string m_variableName;
};
