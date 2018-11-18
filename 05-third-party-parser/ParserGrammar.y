%name ParserGrammar

%token_prefix T_

%token_type {LemonToken}
%default_type {LemonToken}

// Сгенерированная функция продвижения состояния парсера будет принимать 4-й аргумент
%extra_argument {CCalcParser *pParser}

// Этот блок кода запускается при синтаксической ошибке.
%syntax_error {
    (void)yymajor; // глушим предупреждения.
    pParse->OnError(TOKEN); // переменная TOKEN имеет тип, указанный в директиве '%token_type'
}

// Этот блок кода запускается при переполнении стека LALR-парсера
%stack_overflow {
    (void)yypMinor; // глушим предупреждения.
    pParse->OnStackOverflow();
}

// Деструктор будет выполняться перед выбросом токена со стека,
//  в данном случае мы просто глушим предупреждения.
%token_destructor {
    (void)yypParser;
    (void)yypminor;
    (void)pParse;
}

// Код в блоке директивы include попадёт в начало генерируемого файла "*.c"
%include {
    #include <assert.h>
    #include "LemonToken.h"
    #include "CalcParser.h"
} // end %include

program ::= statement(A).
{
    pParser->SetResult(A.value);
}

statement(A) ::= ID(B) ASSIGN add(C).
{
    pParser->SetIdValue(B.id, C.value);
    A.value = C.value;
}

statement(A) ::= add(B).
{
    A.value = B.value;
}

add(A) ::= mult(B).
{
    A.value = B.value;
}

add(A) ::= add(B) PLUS mult(C).
{
    A.value = B.value + C.value;
}

add(A) ::= add(B) SUB mult(C).
{
    A.value = B.value - C.value;
}

mult(A) ::= atom(B).
{
    A.value = B.value;
}

mult(A) ::= mult(B) MUL atom(C).
{
    A.value = B.value * C.value;
}

mult(A) ::= mult(B) DIV atom(C).
{
    A.value = B.value / C.value;
}

atom(A) ::= NUMBER(B).
{
    A.value = B.value;
}

atom(A) ::= ID(B).
{
    A.value = pParser->GetIdValue(B.id);
}

atom(A) ::= OPENING_PARENTHESIS add(B) CLOSING_PARENTHESIS.
{
    A.value = B.value;
}