#include "CalcParser.h"

double CalcParser::Calculate(std::string const& source)
{
    return 1.0;
}

void CalcParser::OnError(LemonToken const& token)
{
    throw std::runtime_error("Error!");
}

void CalcParser::OnStackOverflow()
{
    throw std::runtime_error("Stack overflow!");
}