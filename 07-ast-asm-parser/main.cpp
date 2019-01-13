#include <iostream>
#include <ast/visitor/CodeGenerator.h>
#include "lexer/CalcLexer.h"
#include "parser/CalcParser.h"
#include "ast/visitor/CodeGenerator.h"

int main()
{
    try
    {
        CalcLexer lexer("1+2*3;");
        CalcParser parser;

        auto ast = parser.BuildAst(lexer);
        CodeGenerator generator(ast);
        std::cout << generator.GetResult() << std::endl;
    }
    catch (std::exception const& e)
    {
        std::cout << e.what() << std::endl;
    }
}