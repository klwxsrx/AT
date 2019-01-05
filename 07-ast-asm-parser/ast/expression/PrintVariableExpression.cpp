#include "PrintVariableExpression.h"

PrintVariableExpression::PrintVariableExpression(std::string const& name)
        : m_name(name)
{
}

void PrintVariableExpression::AcceptVisitor(IExpressionVisitor &visitor) const {
    visitor.VariableExpression(m_name);
    visitor.Expression(IExpressionVisitor::Expression::PrintVariable);
}

IExpression *PrintVariableExpression::Left() const {
    return nullptr;
}

IExpression *PrintVariableExpression::Right() const {
    return nullptr;
}
