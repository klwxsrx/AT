#pragma once
#include "Token.h"

class ILexer {
public:
    virtual Token Read() = 0;
    virtual ~ILexer() = default;
};