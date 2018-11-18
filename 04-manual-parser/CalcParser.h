#pragma once
#include <string>
#include <vector>
#include <map>
#include "CalcLexer.h"

class CalcParser {
    typedef std::vector<Token> TokenList;
    typedef std::vector<TokenType> TokenTypeList;

public:
    double Calculate(std::string const& sources);

private:
    void ReadTokens(std::string const& sources);

    double ParseStatement();
    double ParseAdd();
    double ParseMult();
    double ParseAtom();

    bool TryMatch(TokenTypeList const& tokenTypes);
    void TryMatchThrowExceptionOtherwise(TokenTypeList const &tokenTypes);

    void AssignVariable(std::string const& name, double value);
    double GetVariableValue(std::string const& name);

    std::string GetTokenValue(size_t position);

    TokenList m_tokens;
    std::map<std::string, double> m_variables;
    size_t m_tokenPosition;
};