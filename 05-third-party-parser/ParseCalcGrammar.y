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
    #include <assert.h>
    #include "LemonToken.h"
    #include "CalcParser.h"
} // end %include

translation_unit ::= program.

program(A) ::= statement(B) SEMICOLON.
{
    A.value = B.value;
    pParser->SetResult(A.value);
}

program(A) ::= program statement(B) SEMICOLON.
{
    A.value = B.value;
    pParser->SetResult(A.value);
}

program(A) ::= expression(B) SEMICOLON.
{
    A.value = B.value;
    pParser->SetResult(A.value);
}

program(A) ::= program expression(B) SEMICOLON.
{
    A.value = B.value;
    pParser->SetResult(A.value);
}

statement(A) ::= ID(B) ASSIGN expression(C).
{
    pParser->AssignVariable(B.id, C.value);
    A.value = C.value;
    pParser->SetResult(A.value);
}

expression(A) ::= expression(B) PLUS expression(C).
{
    A.value = B.value + C.value;
}

expression(A) ::= expression(B) SUB expression(C).
{
    A.value = B.value - C.value;
}

expression(A) ::= expression(B) MUL expression(C).
{
    A.value = B.value * C.value;
}

expression(A) ::= expression(B) DIV expression(C).
{
    A.value = B.value / C.value;
}

%left PLUS SUB.
%left MUL DIV.

expression(A) ::= OPENING_PARENTHESIS expression(B) CLOSING_PARENTHESIS.
{
    A.value = B.value;
}

expression(A) ::= NUMBER(B).
{
    A.value = B.value;
}

expression(A) ::= ID(B).
{
    A.value = pParser->GetVariableValue(B.id);
}