#include <iostream>
#include <ast/visitor/CodeGenerator.h>
#include "lexer/CalcLexer.h"
#include "parser/CalcParser.h"
#include "ast/visitor/CodeGenerator.h"
#include "compiler/NasmCompilerWrapper.h"

std::string exec(std::string cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}

int main()
{
    try
    {
        CalcLexer lexer("a=1+2*3;b=2+2*2;print a;");
        CalcParser parser;

        auto ast = parser.BuildAst(lexer);
        CodeGenerator generator(ast);

        auto asmCode = generator.GetResult();

        std::cout << asmCode << std::endl;

        std::string executable("calc.exe");
        NasmCompilerWrapper::Compile(asmCode, executable);

        std::cout << "Compiled success! Execution result: \"" << exec("./" + executable) << "\"" << std::endl;
    }
    catch (std::exception const& e)
    {
        std::cout << e.what() << std::endl;
    }
}