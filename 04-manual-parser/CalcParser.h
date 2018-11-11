#pragma once
#include <string>
#include <vector>
#include "CalcLexer.h"

class CalcParser {
    typedef std::vector<Token> TokenList;

public:
    double Calculate(std::string const& sources);

private:
    void ReadTokens(std::string const& sources);

    double ParseStatement();
    //double ParseAdd();
    //double ParseMult();
    //double ParseAtom();

    //bool TryMatch(TokenList& tokens);
    //void Match(TokenList& tokens);
    //void AssignVariable(std::string const& name, double value);

    TokenList m_tokens;
    size_t m_tokenPosition;
};