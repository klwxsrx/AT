#include "CalcLexer.h"

bool IsDigit(char ch)
{
    return ch >= '0' && ch <= '9';
}

bool IsDot(char ch)
{
    return ch == '.';
}

bool IsNumericChar(char ch)
{
    return IsDigit(ch) || IsDot(ch);
}

bool IsZero(char ch)
{
    return ch == '0';
}

bool IsIdChar(char ch)
{
    return isalnum(ch) || ch == '_';
}

CalcLexer::CalcLexer(std::string sources)
    : m_sources(std::move(sources))
{
}

Token CalcLexer::Read()
{
    /*
     * Reads next token from input string with following steps:
     * 1) skips whitespace characters
     * 2) checks for the end of input
     * 3) checks first character to select token type
     * 4) if token may have several characters, read them all
     */

    SkipSpaces();

    if (m_position >= m_sources.size()) {
        return Token{TT_END};
    }

    char next = m_sources[m_position];
    ++m_position;

    switch (next) {
        case '+': return Token{TT_PLUS};
        case '-': return Token{TT_MINUS};
        case '*': return Token{TT_MULT};
        case '/': return Token{TT_DIV};
        case '=': return Token{TT_EQUAL};
        case ';': return Token{TT_SEMICOLON};
        case '(': return Token{TT_LRBRACKET};
        case ')': return Token{TT_RRBRACKET};
        default: break;
    }

    if (IsNumericChar(next)) {
        return ReadNumber(next);
    }

    if (IsIdChar(next)) {
        return ReadId(next);
    }

    return Token{TT_ERROR};
}

void CalcLexer::SkipSpaces()
{
    while (m_position < m_sources.size() && isspace(m_sources[m_position])) {
        ++m_position;
    }
}

Token CalcLexer::ReadNumber(char head)
{
    /*
     * Reads the tail of number token and returns this token.
     * PRECONDITION: first character already read.
     * POSTCONDITION: all number characters have been read.
     */
    std::string value(1, head);
    char current = m_sources[m_position];

    const bool isAnotherDigitAfterZeroChar = IsZero(head) && IsDigit(current);
    bool isValid = IsDigit(head) && !isAnotherDigitAfterZeroChar;

    bool isFraction = false;
    while (m_position < m_sources.size() && IsNumericChar(current)) {
        if (IsDot(current) && !isFraction) {
            isFraction = true;
        }
        else if (IsDot(current) && isFraction) {
            isValid = false;
        }

        value += current;
        current = m_sources[++m_position];
    }

    const bool isCurrentCharId = IsIdChar(current);
    if (isCurrentCharId) {
        ReadId(current);
        return Token{TT_ERROR};
    }

    const bool isLastCharDot = IsDot(m_sources[m_position - 1]);
    if (!isValid || isLastCharDot) {
        return Token{TT_ERROR};
    }

    return Token{TT_NUMBER, value};
}

Token CalcLexer::ReadId(char head)
{
    /*
     * Reads the tail of number token and returns this token.
     * PRECONDITION: first character already read.
     * POSTCONDITION: all id characters have been read.
     */
    std::string value(1, head);

    while (m_position < m_sources.size() && IsIdChar(m_sources[m_position])) {
        value += m_sources[m_position++];
    }

    return Token{TT_ID, value};
}
