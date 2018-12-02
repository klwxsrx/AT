#pragma once
#include <memory>
#include "context/IInterpreterContext.h"

class IExpression {
public:
    typedef std::unique_ptr<IExpression> Ptr;

    virtual double Evaluate(IInterpreterContext & context) const = 0;
    virtual ~IExpression() = default;
};