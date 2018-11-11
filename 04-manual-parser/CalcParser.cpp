#include "CalcParser.h"

double CalcParser::Calculate(std::string const& sources)
{
    ReadTokens(sources);
    if (m_tokens.empty())
    {
        return 0.0;
    }

    double result = 0.0;
    while (m_tokenPosition < m_tokens.size())
    {
        result = ParseStatement();
    }
    return result;
}

void CalcParser::ReadTokens(std::string const& sources)
{
    m_tokenPosition = 0;
    m_tokens.clear();
    if (sources.empty())
    {
        return;
    }

    CalcLexer lexer(sources);
    while (true)
    {
        Token token = lexer.Read();
        if (token.type == TokenType::TT_END)
        {
            break;
        }
        else if (token.type == TokenType::TT_ERROR)
        {
            throw std::runtime_error("Lexical error found!");
        }

        m_tokens.push_back(std::move(token));
    }
}

double CalcParser::ParseStatement()
{
    ++m_tokenPosition;
    return 1.0;
}
