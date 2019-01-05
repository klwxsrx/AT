#pragma once
#include "IExpression.h"

class IExpressionNode {
public:
    virtual IExpression* Left() const = 0;
    virtual IExpression* Right() const = 0;
};
