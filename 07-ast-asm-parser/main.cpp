#include <iostream>
#include <ast/visitor/CodeGenerator.h>
#include "lexer/CalcLexer.h"
#include "parser/CalcParser.h"
#include "ast/visitor/CodeGenerator.h"
#include "compiler/NasmCompilerWrapper.h"

int main()
{
    try
    {
        CalcLexer lexer("(1+2)-(3+4);");
        CalcParser parser;

        auto ast = parser.BuildAst(lexer);
        CodeGenerator generator(ast);

        auto asmCode = generator.GetResult();

        std::string executable("calc.exe");
        NasmCompilerWrapper::Compile(asmCode, executable);

        std::system(executable.c_str());

        std::cout << asmCode << std::endl; // TODO: delete
    }
    catch (std::exception const& e)
    {
        std::cout << e.what() << std::endl;
    }
}