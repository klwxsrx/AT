#pragma once
#include <vector>
#include "ast/expression/IExpression.h"

class AstStatementPool {
    typedef std::vector<IExpression*> ExpressionList;

public:
    void AddStatement(IExpression* expression);
    template <class ExpressionT, class ...TArgs>
    IExpression* CreateExpression(TArgs&&... args)
    {
        static_assert(std::is_base_of<IExpression, ExpressionT>::value);
        m_nodePool.emplace_back(std::make_shared<ExpressionT>(std::forward<TArgs>(args)...));
        return static_cast<IExpression*>(m_nodePool.back().get());
    };
    ExpressionList GetStatements() const;

private:
    ExpressionList m_expressionList;
    std::vector<IExpression::Ptr> m_nodePool;
};