#include "CodeGenerator.h"

CodeGenerator::CodeGenerator(AstStatementPool const& pool)
    : m_pool(pool)
{
    m_pool.GetStatements()[0]->AcceptVisitor(*this);
}

void CodeGenerator::AssignExpression(std::string const &variableName) {
    Append("pop eax");
    Append("mov " + variableName + ", eax");

    AddVariableIfNotExists(variableName);
}

void CodeGenerator::BinaryExpression(IExpressionVisitor::Expression operation) {
    Append("pop ebx");
    Append("pop eax");
    Append(GetAsmOperationByExpression(operation) + " eax, ebx");
    Append("push eax");
}

void CodeGenerator::LiteralExpression(double value) {
    Append("push " + GetAsmDoubleValue(value));
}

void CodeGenerator::VariableExpression(std::string const &variableName) {
    Append("push " + variableName);
}

void CodeGenerator::PrintExpression(double value) {

}

void CodeGenerator::PrintExpression(std::string const &variableName) {

}

std::string CodeGenerator::GetResult()
{
    std::stringstream result;
    result << "Before";
    result << m_result;
    result << "After";
    return result.str();
}

void CodeGenerator::Append(std::string &&code)
{
    m_result.append(code.append("\n"));
}

void CodeGenerator::AddVariableIfNotExists(std::string const &variableName)
{
    if (std::find(m_variables.begin(), m_variables.end(), variableName) == m_variables.end()) {
        m_variables.push_back(variableName);
    }
}

std::string CodeGenerator::GetAsmDoubleValue(double value)
{
    return "__float32__(" + std::to_string(value) + ")";
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


