#include "CalcParser.h"
#include "ParseCalcGrammar.h"

const int END_TOKEN = 0;
const std::map<TokenType, int> CalcParser::m_lemonTokenMap({
    {TT_NUMBER, LT_NUMBER},
    {TT_PLUS, LT_PLUS},
    {TT_MINUS, LT_SUB},
    {TT_MULT, LT_MUL},
    {TT_DIV, LT_DIV},
    {TT_EQUAL, LT_ASSIGN},
    {TT_ID, LT_ID},
    {TT_SEMICOLON, LT_SEMICOLON},
    {TT_LRBRACKET, LT_OPENING_PARENTHESIS},
    {TT_RRBRACKET, LT_CLOSING_PARENTHESIS},
    {TT_PRINT, LT_PRINT},
});

CalcParser::CalcParser()
{
    // Лямбда-функция allocate не захватывает переменных,
    //  и может быть преобразована в указатель на функцию
    auto allocate = [](size_t size) -> void* {
        return new (std::nothrow) char[size];
    };
    m_parser = ParseCalcGrammarAlloc(allocate);
}

CalcParser::~CalcParser()
{
    // Лямбда-функция retain не захватывает переменных,
    //  и может быть преобразована в указатель на функцию
    auto retain = [](void *pointer) -> void {
        auto array = reinterpret_cast<char *>(pointer);
        delete[] array;
    };
    ParseCalcGrammarFree(m_parser, retain);
}

AstStatementPool CalcParser::BuildAst(ILexer & lexer)
{
    m_currentAst = AstStatementPool();
    ParseSources(lexer);
    return m_currentAst;
}

void CalcParser::AddStatement(IExpression* expression)
{
    m_currentAst.AddStatement(expression);
}

void CalcParser::OnError(LemonToken const& token)
{
    throw std::runtime_error("Error while parse expression!");
}

void CalcParser::OnStackOverflow()
{
    throw std::runtime_error("Stack overflow!");
}

void CalcParser::ParseSources(ILexer & lexer)
{
    ReadTokens(lexer);
    if (m_tokens.empty())
    {
        return;
    }

    for (auto const& token : m_tokens)
    {
        ParseCalcGrammar(m_parser, token.type, token, this);
    }
    LemonToken token;
    ParseCalcGrammar(m_parser, END_TOKEN, token, this);
}

void CalcParser::ReadTokens(ILexer & lexer)
{
    m_tokens.clear();
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

        m_tokens.push_back(GetLemonToken(token));
    }
}

LemonToken CalcParser::GetLemonToken(Token const& token)
{
    auto it = m_lemonTokenMap.find(token.type);
    if (it == m_lemonTokenMap.end())
    {
        throw std::runtime_error("Variable not found");
    }

    LemonToken lemonToken;
    lemonToken.type = it->second;

    switch (token.type)
    {
        case TokenType::TT_NUMBER:
            lemonToken.value = std::stod(token.value.value());
            break;
        case TokenType::TT_ID:
            lemonToken.id = new char[token.value.value().length() + 1];
            strcpy(lemonToken.id, token.value.value().c_str());
            break;
        default:
            break;
    }
    return lemonToken;
}