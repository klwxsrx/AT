#pragma once
#include <string>

class IExpressionVisitor {
public:
    enum struct Expression {
        Add,
        Sub,
        Mult,
        Div
    };

    virtual void AssignExpression(std::string const& variableName) = 0;
    virtual void BinaryExpression(Expression operation) = 0;
    virtual void LiteralExpression(double value) = 0;
    virtual void VariableExpression(std::string const& variableName) = 0;
};