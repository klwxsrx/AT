#include <generator.hpp>
#include "CalcLexer.h"

CalcLexer::CalcLexer(std::string sources)
{
    lexertl::generator::build(getRules(), m_lexer);
    m_iterator = lexertl::siterator(sources.begin(), sources.end(), m_lexer);
}

Token CalcLexer::Read()
{
    if (m_iterator == m_end)
    {
        return Token{TT_END};
    }

    const size_t tokenId = m_iterator->id;
    Token token = (tokenId != lexertl::rules::npos()) ? Token{static_cast<TokenType>(tokenId)} : Token{TT_ERROR};
    switch (token.type)
    {
        case TT_ID:
        case TT_NUMBER:
            token.value = m_iterator->str();
            break;
        default:
            break;
    }
    ++m_iterator;
    return token;
}

lexertl::rules CalcLexer::getRules()
{
    lexertl::rules rules;
    rules.push("[ \t\r\n]+", lexertl::rules::skip());
    rules.push(R"text(([\.]|[0][0-9]|.*[.][0-9]*[.]|[0-9.]+[a-zA-Z\_]+)[0-9a-zA-Z\_\.]*)text", TT_ERROR);
    rules.push("[0-9]+[\\.]", TT_ERROR);
    rules.push("([0]|[1-9][0-9]*)([.][0-9]+)?", TT_NUMBER);
    rules.push("[a-zA-Z\\_][a-zA-Z\\_0-9]*", TT_ID);
    rules.push("\\+", TT_PLUS);
    rules.push("\\-", TT_MINUS);
    rules.push("\\*", TT_MULT);
    rules.push("\\/", TT_DIV);
    rules.push("\\=", TT_EQUAL);
    rules.push("\\;", TT_SEMICOLON);
    rules.push("\\(", TT_LRBRACKET);
    rules.push("\\)", TT_RRBRACKET);
    return rules;
}