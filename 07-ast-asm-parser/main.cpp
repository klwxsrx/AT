#include <iostream>
#include "lexer/CalcLexer.h"
#include "parser/CalcParser.h"

int main()
{
    try
    {
        CalcLexer lexer("a=1+2*3;print a");
        CalcParser parser;

        auto ast = parser.BuildAst(lexer);
    }
    catch (std::exception const& e)
    {
        std::cout << e.what() << std::endl;
    }
    int i = 0;
}