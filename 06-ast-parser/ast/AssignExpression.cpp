#include "AssignExpression.h"

AssignExpression::AssignExpression(std::string const& variableName, Ptr && expression)
    : m_variableName(variableName), m_expression(std::move(expression))
{
}

double AssignExpression::Evaluate(IInterpreterContext &context) const {
    double value = m_expression->Evaluate(context);
    context.AssignVariable(m_variableName, value);
    return value;
}
