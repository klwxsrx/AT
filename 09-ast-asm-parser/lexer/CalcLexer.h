#pragma once

#include <string>
#include <cctype>
#include "ILexer.h"

class CalcLexer : public ILexer
{
public:
    explicit CalcLexer(std::string sources);
    Token Read() override;

private:
    void SkipSpaces();
    Token ReadWord(char head);
    Token ReadNumber(char head);

    static const std::string m_printExpressionName;

    std::string m_sources;
    size_t m_position = 0;
};