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
            throw std::runtime_error("Error token found!");
        }

        m_tokens.push_back(std::move(token));
    }
}

double CalcParser::ParseStatement()
{
    if (TryMatch({TokenType::TT_ID, TT_EQUAL}))
    {
        std::string variableName = GetTokenValue(m_tokenPosition - 2); // m_tokenPosition was incremented by two matched tokens

        double result = ParseAdd();
        AssignVariable(variableName, result);
        TryMatchThrowOtherwise({TokenType::TT_SEMICOLON});
        return result;
    }

    double result = ParseAdd();
    TryMatchThrowOtherwise({TokenType::TT_SEMICOLON});
    return result;
}

double CalcParser::ParseAdd()
{
    double result = ParseMult();
    while (true)
    {
        if (TryMatch({TokenType::TT_PLUS}))
        {
            result += ParseMult();
        }
        else if (TryMatch({TokenType::TT_MINUS}))
        {
            result -= ParseMult();
        }
        else
        {
            break;
        }
    }
    return result;
}

double CalcParser::ParseMult()
{
    double result = ParseAtom();
    while (true)
    {
        if (TryMatch({TokenType::TT_MULT}))
        {
            result *= ParseAtom();
        }
        else if (TryMatch({TokenType::TT_DIV}))
        {
            result /= ParseAtom();
        }
        else
        {
            break;
        }
    }
    return result;
}

double CalcParser::ParseAtom()
{
    if (TryMatch({TT_NUMBER}))
    {
        return std::stod(GetTokenValue(m_tokenPosition - 1));
    }
    else if (TryMatch({TT_ID}))
    {
        return GetVariableValue(GetTokenValue(m_tokenPosition - 1));
    }

    TryMatchThrowOtherwise({TT_LRBRACKET});
    double result = ParseAdd();
    TryMatchThrowOtherwise({TT_RRBRACKET});

    return result;
}

bool CalcParser::TryMatch(TokenTypeList const& tokenTypes)
{
    size_t currentPosition = m_tokenPosition;
    for (const TokenType tokenType : tokenTypes)
    {
        if (currentPosition == m_tokens.size() || m_tokens[currentPosition].type != tokenType)
        {
            return false;
        }
        ++currentPosition;
    }
    m_tokenPosition = currentPosition;
    return true;
}

void CalcParser::TryMatchThrowOtherwise(TokenTypeList const &tokenTypes)
{
    if (!TryMatch(tokenTypes))
    {
        throw std::runtime_error("Token does not match!");
    }
}

void CalcParser::AssignVariable(std::string const& name, double value)
{
    m_variables[name] = value;
}

double CalcParser::GetVariableValue(std::string const& name)
{
    auto it = m_variables.find(name);
    if (it == m_variables.end())
    {
        throw std::runtime_error("Variable not found");
    }
    return it->second;
}

std::string CalcParser::GetTokenValue(size_t position)
{
    if (position >= m_tokens.size())
    {
        throw std::runtime_error("Token not exists");
    }

    Token& token = m_tokens[position];
    if (!token.value)
    {
        throw std::runtime_error("Token hasn't value");
    }
    return *token.value;
}