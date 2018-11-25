#include "CalcParser.h"

double CalcParser::Calculate(std::string const& source)
{
    return 1.0;
}

double CalcParser::GetIdValue(const char* id) const
{
    auto it = m_variables.find(id);
    if (it == m_variables.end())
    {
        throw std::runtime_error("Variable not found");
    }
    return it->second;
}

void CalcParser::SetIdValue(const char* id, double value)
{
    m_variables[id] = value;
}

void CalcParser::SetResult(double result)
{
    m_result = result;
}

void CalcParser::OnError(LemonToken const& token)
{
    throw std::runtime_error("Error while parse expression!");
}

void CalcParser::OnStackOverflow()
{
    throw std::runtime_error("Stack overflow!");
}