#pragma once
#include <sstream>
#include <vector>
#include <algorithm>
#include "IExpressionVisitor.h"
#include "../AstStatementPool.h"

class CodeGenerator : public IExpressionVisitor {
public:
    explicit CodeGenerator(AstStatementPool const& pool);

    void AssignExpression(std::string const &variableName) override;
    void BinaryExpression(Expression operation) override;
    void LiteralExpression(double value) override;
    void VariableExpression(std::string const &variableName) override;
    void PrintExpression(std::string const &variableName) override;


    std::string GetResult();
private:
    void Append(std::string &&code);
    void AddVariableIfNotExists(std::string const &variableName);

    static std::string GetAsmDoubleValue(double value);
    static std::string GetAsmOperationByExpression(IExpressionVisitor::Expression expresion);

    AstStatementPool m_pool;
    std::vector<std::string> m_variables;

    std::string m_result;
};
