#pragma once
#include "IExpression.h"
#include "IExpressionNode.h"

class PrintVariableExpression : public IExpression, public IExpressionNode {
public:
    explicit PrintVariableExpression(std::string const& value);

    void AcceptVisitor(IExpressionVisitor &visitor) const override;
    IExpression *Left() const override;
    IExpression *Right() const override;

private:
    std::string m_name;
};