#pragma once
#include <string>
#include "CalcLexer.h"

namespace calc
{
class CalcParser {
public:
    explicit CalcParser(CalcLexer& lexer);
    double Calculate(std::string sources);

private:
    CalcLexer& m_lexer;
};
}