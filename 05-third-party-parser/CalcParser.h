#pragma once

#include <exception>
#include <map>
#include <vector>
#include <string.h>
#include "ICalcParser.h"
#include "LemonToken.h"
#include "CalcLexer.h"

class CalcParser final : public ICalcParser {
    typedef std::vector<LemonToken> TokenList;
public:
    CalcParser();
    ~CalcParser() override;

    double Calculate(std::string const& source) override;

    double GetIdValue(const char *id) const;
    void SetIdValue(const char *id, double value);
    void SetResult(double result);
    void OnError(LemonToken const& token);
    void OnStackOverflow();

private:
    void ReadTokens(std::string const& sources);
    static LemonToken GetLemonToken(Token const& token);

    void* m_parser = nullptr;

    TokenList m_tokens;
    std::map<std::string, double> m_variables;
    double m_result = 0;
    static const std::map<TokenType, int> m_lemonTokenMap;
};

void* ParseCalcGrammarAlloc(void *(*mallocProc)(size_t));
void ParseCalcGrammar(void*, int, LemonToken, CalcParser*);
void ParseCalcGrammarFree(
        void *p,                    /* The parser to be deleted */
        void (*freeProc)(void*)     /* Function used to reclaim memory */);