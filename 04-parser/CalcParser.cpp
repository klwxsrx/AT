#include "CalcParser.h"

namespace calc
{
CalcParser::CalcParser(calc::CalcLexer &lexer)
    : m_lexer(lexer)
{
}

double CalcParser::Calculate(std::string sources)
{
    if (sources.empty())
    {
        return 0.0;
    }

    return 1.0;
}
}
