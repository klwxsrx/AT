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
};

struct Token
{
    TokenType type = TT_END;
    std::experimental::optional<std::string> value;
};

}
