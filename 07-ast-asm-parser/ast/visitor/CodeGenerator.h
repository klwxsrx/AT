#pragma once
#include <vector>
#include "IExpressionVisitor.h"
#include "../AstStatementPool.h"

class CodeGenerator : public IExpressionVisitor {
public:
    explicit CodeGenerator(AstStatementPool const& pool);

    void AssignExpression(std::string const &variableName) override;
    void BinaryExpression(Expression operation) override;
    void LiteralExpression(double value) override;
    void VariableExpression(std::string const &variableName) override;


    std::string GetResult();
private:
    void Append(std::string &&code);
    static std::string GetAsmOperationByExpression(IExpressionVisitor::Expression expresion);

    AstStatementPool m_pool;
    std::vector<std::string> m_variables;

    std::string m_result;
};
