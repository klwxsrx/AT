%name ParseCalcGrammar

%token_prefix LT_

%token_type {LemonToken}
%default_type {LemonToken}

// Сгенерированная функция продвижения состояния парсера будет принимать 4-й аргумент
%extra_argument {CalcParser *pParser}

// Этот блок кода запускается при синтаксической ошибке.
%syntax_error {
    (void)yymajor; // глушим предупреждения.
    pParser->OnError(TOKEN); // переменная TOKEN имеет тип, указанный в директиве '%token_type'
}

// Этот блок кода запускается при переполнении стека LALR-парсера
%stack_overflow {
    pParser->OnStackOverflow();
}

// Деструктор будет выполняться перед выбросом токена со стека,
//  в данном случае мы просто глушим предупреждения.
%token_destructor {
    (void)yypParser;
    (void)yypminor;
    (void)pParser;
}

// Код в блоке директивы include попадёт в начало генерируемого файла "*.c"
%include {
    #include <memory>
    #include <assert.h>
    #include "grammar/LemonToken.h"
    #include "parser/CalcParser.h"
    #include "ast/expression/AssignExpression.h"
    #include "ast/expression/BinaryExpression.h"
    #include "ast/expression/LiteralExpression.h"
    #include "ast/expression/VariableExpression.h"

    struct SRecord
    {
        IExpression* expr;
    };

} // end %include

translation_unit ::= statement.

statement ::= statement PRINT NUMBER(A).
{
    pParser->AddStatement(pParser->CreateExpression<PrintLiteralExpression>(A.value));
}

statement ::= statement PRINT ID(A).
{
    pParser->AddStatement(pParser->CreateExpression<PrintVariableExpression>(A.id));
}

statement ::= various_expression(B) SEMICOLON.
{
    pParser->AddStatement(B.expr);
}

statement ::= statement various_expression(B) SEMICOLON.
{
    pParser->AddStatement(B.expr);
}

various_expression(A) ::= expression(B).
{
    A.expr = B.expr;
}

various_expression(A) ::= expression_with_assign(B).
{
    A.expr = B.expr;
}

expression_with_assign(A) ::= ID(B) ASSIGN expression(C).
{
    A.expr = pParser->CreateExpression<AssignExpression>(B.id, C.expr);
}

expression(A) ::= expression(B) PLUS expression(C).
{
    A.expr = pParser->CreateExpression<BinaryExpression>(B.expr, BinaryExpression::Operation::Add, C.expr);
}

expression(A) ::= expression(B) SUB expression(C).
{
    A.expr = pParser->CreateExpression<BinaryExpression>(B.expr, BinaryExpression::Operation::Sub, C.expr);
}

expression(A) ::= expression(B) MUL expression(C).
{
    A.expr = pParser->CreateExpression<BinaryExpression>(B.expr, BinaryExpression::Operation::Mult, C.expr);
}

expression(A) ::= expression(B) DIV expression(C).
{
    A.expr = pParser->CreateExpression<BinaryExpression>(B.expr, BinaryExpression::Operation::Div, C.expr);
}

%left PLUS SUB.
%left MUL DIV.

expression(A) ::= OPENING_PARENTHESIS expression(B) CLOSING_PARENTHESIS.
{
    A.expr = B.expr;
}

expression(A) ::= NUMBER(B).
{
    A.expr = pParser->CreateExpression<LiteralExpression>(B.value);
}

expression(A) ::= ID(B).
{
    A.expr = pParser->CreateExpression<VariableExpression>(B.id);
}

%type various_expression SRecord
%type expression SRecord
%type expression_with_assign SRecord