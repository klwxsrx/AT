#include "CodeGenerator.h"

CodeGenerator::CodeGenerator(AstStatementPool const& pool)
    : m_pool(pool)
{
    for (auto statement : m_pool.GetStatements()) {
        statement->AcceptVisitor(*this);
    }
}

void CodeGenerator::AssignExpression(std::string const &variableName) {
    Append("pop eax");
    Append("mov " + variableName + ", eax");

    AddVariableIfNotExists(variableName);
}

void CodeGenerator::BinaryExpression(IExpressionVisitor::Expression operation) {
    Append("call " + GetAsmOperationByExpression(operation));
}

void CodeGenerator::LiteralExpression(double value) {
    Append("push " + GetAsmDoubleValue(value));
}

void CodeGenerator::VariableExpression(std::string const &variableName) {
    Append("push " + variableName);
}

void CodeGenerator::PrintExpression(std::string const &variableName) {
    Append("printf " + variableName);
}

std::string CodeGenerator::GetResult()
{
    std::stringstream result;
    result << R"code(
global main
extern printf

section .text
    _print_and_exit:
        pop rbx
        sub rsp, 8
        movq xmm0, rbx
        cvtss2sd xmm0, xmm0
        mov rdi, print_format
        mov rax, 1
        call printf
        add rsp, 8
		ret

	_add:
		pop rcx ; save ret location
		pop rbx
		movq xmm0, rbx
		pop rax
		movq xmm1, rax
		addss xmm0, xmm1
		movq rbx, xmm0
		push rbx
		push rcx ; restore ret location
		ret

	_sub:
		pop rcx ; save ret location
		pop rbx
		movq xmm0, rbx
		pop rax
		movq xmm1, rax
		subss xmm0, xmm1
		movq rbx, xmm0
		push rbx
		push rcx ; restore ret location
		ret

	_mul:
		pop rcx ; save ret location
		pop rbx
		movq xmm0, rbx
		pop rax
		movq xmm1, rax
		mulss xmm0, xmm1
		movq rbx, xmm0
		push rbx
		push rcx ; restore ret location
		ret

	_div:
		pop rcx ; save ret location
		pop rbx
		movq xmm0, rbx
		pop rax
		movq xmm1, rax
		divss xmm0, xmm1
		movq rbx, xmm0
		push rbx
		push rcx ; restore ret location
		ret

	main:
)code";
    result << m_result;
    result << R"code(        pop rax ; pop last item
        ret
section .bss
)code";
    result << GenerateBssSection();
    result << R"code(
section .data
	print_format db `%f`, 0
)code";
    return result.str();
}

void CodeGenerator::Append(std::string &&code)
{
    m_result.append("\t\t" + code.append("\n"));
}

void CodeGenerator::AddVariableIfNotExists(std::string const &variableName)
{
    if (std::find(m_variables.begin(), m_variables.end(), variableName) == m_variables.end()) {
        m_variables.push_back(variableName);
    }
}

std::string CodeGenerator::GenerateBssSection()
{
    return ""; // TODO:
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
            return "_add";
        case IExpressionVisitor::Expression::Sub:
            return "_sub";
        case IExpressionVisitor::Expression::Mult:
            return "_mul";
        case IExpressionVisitor::Expression::Div:
            return "_div";
        default:
            throw std::runtime_error("Undefined asm operation!");
    }
}


