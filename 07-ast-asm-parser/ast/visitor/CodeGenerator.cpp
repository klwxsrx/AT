#include "CodeGenerator.h"

CodeGenerator::CodeGenerator(AstStatementPool const& pool)
    : m_pool(pool)
{
    m_pool.GetStatements()[0]->AcceptVisitor(*this);
}

void CodeGenerator::AssignExpression(std::string const &variableName) {
    Append("pop ax");
    Append("mov " + variableName + " ax");
}

void CodeGenerator::BinaryExpression(IExpressionVisitor::Expression operation) {
    Append("pop bx"); // TODO: порядок получения из стека
    Append("pop ax");
    Append(GetAsmOperationByExpression(operation) + " ax bx");
    Append("push ax");
}

void CodeGenerator::LiteralExpression(double value) {
    Append("push " + std::to_string(value));
}

void CodeGenerator::VariableExpression(std::string const &variableName) {
    Append("push " + variableName);
}

std::string CodeGenerator::GetResult()
{
    return m_result;
}

void CodeGenerator::Append(std::string &&code)
{
    m_result.append(code.append("\n"));
}

std::string CodeGenerator::GetAsmOperationByExpression(IExpressionVisitor::Expression expresion)
{
    switch (expresion)
    {
        case IExpressionVisitor::Expression::Add:
            return "add";
        case IExpressionVisitor::Expression::Sub:
            return "sub";
        case IExpressionVisitor::Expression::Mult:
            return "mul";
        case IExpressionVisitor::Expression::Div:
            return "div";
        default:
            throw std::runtime_error("Undefined asm operation!");
    }
}


