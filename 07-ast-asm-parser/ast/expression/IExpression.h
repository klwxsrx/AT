#pragma once
#include <memory>
#include "context/IInterpreterContext.h"

class IExpression {
public:
    typedef std::shared_ptr<IExpression> Ptr;

    virtual double Evaluate(IInterpreterContext & context) const = 0; // TODO: delete
    virtual ~IExpression() = default;
};