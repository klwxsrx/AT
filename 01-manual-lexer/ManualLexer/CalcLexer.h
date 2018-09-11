#pragma once

#include <string>
#include <cctype>
#include "Token.h"

namespace calc
{

class CalcLexer
{
public:
    explicit CalcLexer(std::string sources);
    Token Read();

private:
    void SkipSpaces();
    Token ReadNumber(char head);

    std::string m_sources;
    size_t m_position = 0;
};

}
