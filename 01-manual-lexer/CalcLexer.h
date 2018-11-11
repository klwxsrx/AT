#pragma once

#include <string>
#include <cctype>
#include "Token.h"

class CalcLexer
{
public:
    explicit CalcLexer(std::string sources);
    Token Read();

private:
    void SkipSpaces();
    Token ReadId(char head);
    Token ReadNumber(char head);

    std::string m_sources;
    size_t m_position = 0;
};