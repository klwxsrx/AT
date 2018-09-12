#pragma once

#include <string>
#include <experimental/optional>

namespace calc
{

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
};

struct Token
{
    TokenType type = TT_END;
    std::experimental::optional<std::string> value;
};

}
