#pragma once
#include <memory>
#include "ast/visitor/IExpressionVisitor.h"

class IExpression {
public:
    typedef std::shared_ptr<IExpression> Ptr;

    virtual void AcceptVisitor(IExpressionVisitor& visitor) const = 0;
    virtual ~IExpression() = default;
};