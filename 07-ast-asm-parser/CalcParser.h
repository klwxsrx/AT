#pragma once

#include <exception>
#include <map>
#include <vector>
#include <string.h>
#include "LemonToken.h"
#include "ast/expression/IExpression.h"
#include "ast/AstStatementPool.h"
#include "context/InterpreterContext.h"
#include "lexer/ILexer.h"

class CalcParser final {
    typedef std::vector<LemonToken> TokenList;
public:
    CalcParser();
    ~CalcParser();

    AstStatementPool BuildAst(ILexer & lexer);
    void AddStatement(IExpression* expression);

    template <class ExpressionT, class ...TArgs>
    IExpression* CreateExpression(TArgs&&... args)
    {
        return m_currentAst.CreateExpression(std::forward<TArgs>(args)...);
    };

    void OnError(LemonToken const& token);
    void OnStackOverflow();

private:
    void ParseSources(ILexer & lexer);
    void ReadTokens(ILexer & lexer);

    static LemonToken GetLemonToken(Token const& token);

    void* m_parser = nullptr;

    TokenList m_tokens;
    InterpeterContext m_interpreterContext;
    AstStatementPool m_currentAst;

    static const std::map<TokenType, int> m_lemonTokenMap;
};

void* ParseCalcGrammarAlloc(void *(*mallocProc)(size_t));
void ParseCalcGrammar(void*, int, LemonToken, CalcParser*);
void ParseCalcGrammarFree(
        void *p,                    /* The parser to be deleted */
        void (*freeProc)(void*)     /* Function used to reclaim memory */);