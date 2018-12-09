#pragma once

#include <exception>
#include <map>
#include <vector>
#include <string.h>
#include <ast/LiteralExpression.h>
#include <ast/VariableExpression.h>
#include <ast/BinaryExpression.h>
#include <ast/AssignExpression.h>
#include "ICalcParser.h"
#include "LemonToken.h"
#include "CalcLexer.h"
#include "context/InterpreterContext.h"
#include "ast/IExpression.h"

class CalcParser final : public ICalcParser {
    typedef std::vector<LemonToken> TokenList;
    typedef std::vector<IExpression*> ExpressionList;
public:
    CalcParser();
    ~CalcParser() override;

    double Calculate(std::string const& source) override;
    void AddStatement(IExpression* expression);

    template <class ExpressionT, class ...TArgs>
    IExpression* CreateExpression(TArgs&&... args)
    {
        static_assert(std::is_base_of<IExpression, ExpressionT>::value);
        m_nodePool.emplace_back(std::make_unique<ExpressionT>(std::forward<TArgs>(args)...));
        return static_cast<IExpression*>(m_nodePool.back().get());
    };

    void OnError(LemonToken const& token);
    void OnStackOverflow();

private:
    void ParseSources(std::string const& sources);

    void ReadTokens(std::string const& sources);
    static LemonToken GetLemonToken(Token const& token);

    void* m_parser = nullptr;

    TokenList m_tokens;
    InterpeterContext m_interpreterContext;
    ExpressionList m_expressionList;
    std::vector<IExpression::Ptr> m_nodePool;
    static const std::map<TokenType, int> m_lemonTokenMap;
};

void* ParseCalcGrammarAlloc(void *(*mallocProc)(size_t));
void ParseCalcGrammar(void*, int, LemonToken, CalcParser*);
void ParseCalcGrammarFree(
        void *p,                    /* The parser to be deleted */
        void (*freeProc)(void*)     /* Function used to reclaim memory */);