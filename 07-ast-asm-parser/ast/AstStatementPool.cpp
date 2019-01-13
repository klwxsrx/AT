#include "AstStatementPool.h"

void AstStatementPool::AddStatement(IExpression* expression)
{
    m_expressionList.push_back(expression);
}

AstStatementPool::ExpressionList AstStatementPool::GetStatements() const
{
    return m_expressionList;
}