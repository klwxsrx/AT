#pragma once

#include <string>
#include <iterator.hpp>
#include <rules.hpp>
#include "Token.h"

class CalcLexer
{
public:
    explicit CalcLexer(std::string sources);
    Token Read();

private:
    static lexertl::rules getRules();

    lexertl::state_machine m_lexer;
    lexertl::siterator m_iterator;
    lexertl::siterator m_end;
};
