#pragma once

class IExpressionVisitor {
public:
    enum struct Expression {
        Add,
        Sub,
        Mult,
        Div,
        Assign,
        PrintLiteral,
        PrintVariable
    };

    virtual void Expression(Expression expression) = 0;
    virtual void LiteralExpression(double value) = 0;
    virtual void VariableExpression(std::string const& name) = 0;
};