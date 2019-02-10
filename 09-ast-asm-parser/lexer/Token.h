#pragma once

#include <string>
#include <experimental/optional>

enum TokenType
{
    TT_END = 0,
    TT_ERROR,
    TT_NUMBER,
    TT_PLUS,
    TT_MINUS,
    TT_MULT,
    TT_DIV,
    TT_EQUAL,
    TT_ID,
    TT_SEMICOLON,
    TT_LRBRACKET,
    TT_RRBRACKET,
    TT_PRINT,
};

struct Token
{
    TokenType type = TT_END;
    std::experimental::optional<std::string> value;
};