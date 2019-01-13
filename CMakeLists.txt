cmake_minimum_required(VERSION 3.10)
project(AT)

set(CMAKE_CXX_STANDARD 17)

### CATCH2 ###
add_library(Catch2 lib/catch2/catch.hpp)
target_include_directories(Catch2 PUBLIC lib/catch2)
set_target_properties(Catch2 PROPERTIES LINKER_LANGUAGE CXX)

### LEXERTL ###
add_library(Lexertl lib/lexertl/iterator.hpp lib/lexertl/rules.hpp lib/lexertl/generator.hpp)
target_include_directories(Lexertl PUBLIC lib/lexertl)
set_target_properties(Lexertl PROPERTIES LINKER_LANGUAGE CXX)

### LEMON ###
add_executable(Lemon lib/lemon/lemon.c)
set_target_properties(Lemon PROPERTIES LINKER_LANGUAGE C)

### COMMON ###
add_library(Common 00-common/Token.h)
target_include_directories(Common PUBLIC 00-common)
set_target_properties(Common PROPERTIES LINKER_LANGUAGE CXX)

### MANUAL LEXER ###
add_library(ManualLexer 01-manual-lexer/CalcLexer.h 01-manual-lexer/CalcLexer.cpp)
target_include_directories(ManualLexer PUBLIC 01-manual-lexer)
target_link_libraries(ManualLexer Common)

### MANUAL LEXER TESTS ###
add_executable(ManualLexerTests 03-lexer-tests/CalcLexerTests.cpp 03-lexer-tests/main.cpp)
target_link_libraries(ManualLexerTests Catch2 ManualLexer)

### THIRD PARTY LEXER ####
add_library(ThirdPartyLexer 02-third-party-lexer/CalcLexer.h 02-third-party-lexer/CalcLexer.cpp)
target_include_directories(ThirdPartyLexer PUBLIC 02-third-party-lexer)
target_link_libraries(ThirdPartyLexer Common Lexertl)

### THIRD PARTY LEXER TESTS ###
add_executable(ThirdPartyLexerTests 03-lexer-tests/CalcLexerTests.cpp 03-lexer-tests/main.cpp)
target_link_libraries(ThirdPartyLexerTests Catch2 ThirdPartyLexer)

### MANUAL PARSER ###
add_library(ManualParser 04-manual-parser/CalcParser.h 04-manual-parser/CalcParser.cpp)
target_include_directories(ManualParser PUBLIC 04-manual-parser)
target_link_libraries(ManualParser ManualLexer)

### MANUAL PARSER TESTS ###
add_executable(ManualParserTests 08-parser-tests/CalcParserTests.cpp 08-parser-tests/main.cpp)
target_link_libraries(ManualParserTests Catch2 ManualParser)

### MANUAL PARSER UI ###
add_executable(ManualParserUI 09-parser-ui/main.cpp)
target_link_libraries(ManualParserUI ManualParser)

### THIRD PARTY PARSER ###
add_library(ThirdPartyParser
        05-third-party-parser/ICalcParser.h
        05-third-party-parser/LemonToken.h
        05-third-party-parser/CalcParser.h
        05-third-party-parser/CalcParser.cpp
        05-third-party-parser/ParseCalcGrammar.h
        05-third-party-parser/ParseCalcGrammar.cpp)
target_include_directories(ThirdPartyParser PUBLIC 05-third-party-parser)
target_link_libraries(ThirdPartyParser ManualLexer)
add_custom_command(
        OUTPUT 05-third-party-parser/ParseCalcGrammar.h 05-third-party-parser/ParseCalcGrammar.cpp
        COMMAND Lemon -q -l -s ${CMAKE_SOURCE_DIR}/05-third-party-parser/ParseCalcGrammar.y -d${CMAKE_SOURCE_DIR}/05-third-party-parser/ -T${CMAKE_SOURCE_DIR}/lib/lemon/lempar.c
        COMMAND sed -i 's/typedef union {/typedef union U {\\nU\(\){}\;\\n~U\(\){}\;/g' ${CMAKE_SOURCE_DIR}/05-third-party-parser/ParseCalcGrammar.c
        COMMAND sed -i '/YYMINORTYPE yylhsminor\;/d' ${CMAKE_SOURCE_DIR}/05-third-party-parser/ParseCalcGrammar.c
        COMMAND sed -i '/switch\( yyruleno \){/i YYMINORTYPE yylhsminor\;' ${CMAKE_SOURCE_DIR}/05-third-party-parser/ParseCalcGrammar.c
        COMMAND ${CMAKE_COMMAND} -E rename ${CMAKE_SOURCE_DIR}/05-third-party-parser/ParseCalcGrammar.c ${CMAKE_SOURCE_DIR}/05-third-party-parser/ParseCalcGrammar.cpp
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/05-third-party-parser/ParseCalcGrammar.cpp ${CMAKE_BINARY_DIR}/05-third-party-parser/ParseCalcGrammar.cpp)
add_custom_command(TARGET ThirdPartyParser POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_SOURCE_DIR}/05-third-party-parser/ParseCalcGrammar.h
        COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_SOURCE_DIR}/05-third-party-parser/ParseCalcGrammar.cpp
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/05-third-party-parser)

### THIRD PARTY PARSER TESTS ###
add_executable(ThirdPartyParserTests 08-parser-tests/CalcParserTests.cpp 08-parser-tests/main.cpp)
target_link_libraries(ThirdPartyParserTests Catch2 ThirdPartyParser)

### AST PARSER ###
add_library(AstParser
        06-ast-parser/ICalcParser.h
        06-ast-parser/LemonToken.h
        06-ast-parser/CalcParser.h
        06-ast-parser/CalcParser.cpp
        06-ast-parser/ast/IExpression.h
        06-ast-parser/ast/BinaryExpression.h
        06-ast-parser/ast/BinaryExpression.cpp
        06-ast-parser/context/IInterpreterContext.h
        06-ast-parser/ast/LiteralExpression.cpp
        06-ast-parser/ast/LiteralExpression.h
        06-ast-parser/ast/VariableExpression.cpp
        06-ast-parser/ast/VariableExpression.h
        06-ast-parser/ast/AssignExpression.cpp
        06-ast-parser/ast/AssignExpression.h
        06-ast-parser/context/InterpreterContext.cpp
        06-ast-parser/context/InterpreterContext.h
        06-ast-parser/ParseCalcGrammar.h
        06-ast-parser/ParseCalcGrammar.cpp)
target_include_directories(AstParser PUBLIC 06-ast-parser)
target_include_directories(AstParser PRIVATE ${CMAKE_BINARY_DIR})
target_link_libraries(AstParser ManualLexer)
add_custom_command(
        OUTPUT 06-ast-parser/ParseCalcGrammar.h 06-ast-parser/ParseCalcGrammar.cpp
        COMMAND Lemon -q -l -s ${CMAKE_SOURCE_DIR}/06-ast-parser/ParseCalcGrammar.y -d${CMAKE_SOURCE_DIR}/06-ast-parser/ -T${CMAKE_SOURCE_DIR}/lib/lemon/lempar.c
        COMMAND sed -i 's/typedef union {/typedef union U {\\nU\(\){}\;\\n~U\(\){}\;/g' ${CMAKE_SOURCE_DIR}/06-ast-parser/ParseCalcGrammar.c
        COMMAND sed -i '/YYMINORTYPE yylhsminor\;/d' ${CMAKE_SOURCE_DIR}/06-ast-parser/ParseCalcGrammar.c
        COMMAND sed -i '/switch\( yyruleno \){/i YYMINORTYPE yylhsminor\;' ${CMAKE_SOURCE_DIR}/06-ast-parser/ParseCalcGrammar.c
        COMMAND ${CMAKE_COMMAND} -E rename ${CMAKE_SOURCE_DIR}/06-ast-parser/ParseCalcGrammar.c ${CMAKE_SOURCE_DIR}/06-ast-parser/ParseCalcGrammar.cpp
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/06-ast-parser/ParseCalcGrammar.cpp ${CMAKE_BINARY_DIR}/06-ast-parser/ParseCalcGrammar.cpp)
add_custom_command(TARGET AstParser POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_SOURCE_DIR}/06-ast-parser/ParseCalcGrammar.h
        COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_SOURCE_DIR}/06-ast-parser/ParseCalcGrammar.cpp
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/06-ast-parser)

### AST PARSER TESTS ###
add_executable(AstParserTests 08-parser-tests/CalcParserTests.cpp 08-parser-tests/main.cpp)
target_link_libraries(AstParserTests Catch2 AstParser)

### AST ASM PARSER ###
add_executable(AstAsmParser
        07-ast-asm-parser/grammar/LemonToken.h
        07-ast-asm-parser/parser/CalcParser.h
        07-ast-asm-parser/parser/CalcParser.cpp
        07-ast-asm-parser/lexer/Token.h
        07-ast-asm-parser/lexer/CalcLexer.h
        07-ast-asm-parser/lexer/CalcLexer.cpp
        07-ast-asm-parser/ast/AstStatementPool.h
        07-ast-asm-parser/ast/AstStatementPool.cpp
        07-ast-asm-parser/ast/expression/IExpression.h
        07-ast-asm-parser/ast/expression/AssignExpression.h
        07-ast-asm-parser/ast/expression/AssignExpression.cpp
        07-ast-asm-parser/ast/expression/BinaryExpression.h
        07-ast-asm-parser/ast/expression/BinaryExpression.cpp
        07-ast-asm-parser/ast/expression/LiteralExpression.cpp
        07-ast-asm-parser/ast/expression/LiteralExpression.h
        07-ast-asm-parser/ast/expression/VariableExpression.cpp
        07-ast-asm-parser/ast/expression/VariableExpression.h
        07-ast-asm-parser/ast/visitor/IExpressionVisitor.h
        07-ast-asm-parser/ast/visitor/CodeGenerator.cpp
        07-ast-asm-parser/ast/visitor/CodeGenerator.h
        07-ast-asm-parser/ParseCalcGrammar.h
        07-ast-asm-parser/ParseCalcGrammar.cpp
        07-ast-asm-parser/main.cpp 07-ast-asm-parser/compiler/NasmCompilerWrapper.cpp 07-ast-asm-parser/compiler/NasmCompilerWrapper.h)
target_include_directories(AstAsmParser PUBLIC 07-ast-asm-parser)
target_include_directories(AstAsmParser PRIVATE ${CMAKE_BINARY_DIR})
add_custom_command(
        OUTPUT 07-ast-asm-parser/ParseCalcGrammar.h 07-ast-asm-parser/ParseCalcGrammar.cpp
        COMMAND Lemon -q -l -s ${CMAKE_SOURCE_DIR}/07-ast-asm-parser/grammar/ParseCalcGrammar.y -d${CMAKE_SOURCE_DIR}/07-ast-asm-parser/ -T${CMAKE_SOURCE_DIR}/lib/lemon/lempar.c
        COMMAND sed -i 's/typedef union {/typedef union U {\\nU\(\){}\;\\n~U\(\){}\;/g' ${CMAKE_SOURCE_DIR}/07-ast-asm-parser/ParseCalcGrammar.c
        COMMAND sed -i '/YYMINORTYPE yylhsminor\;/d' ${CMAKE_SOURCE_DIR}/07-ast-asm-parser/ParseCalcGrammar.c
        COMMAND sed -i '/switch\( yyruleno \){/i YYMINORTYPE yylhsminor\;' ${CMAKE_SOURCE_DIR}/07-ast-asm-parser/ParseCalcGrammar.c
        COMMAND ${CMAKE_COMMAND} -E rename ${CMAKE_SOURCE_DIR}/07-ast-asm-parser/ParseCalcGrammar.c ${CMAKE_SOURCE_DIR}/07-ast-asm-parser/ParseCalcGrammar.cpp
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/07-ast-asm-parser/ParseCalcGrammar.cpp ${CMAKE_BINARY_DIR}/07-ast-asm-parser/ParseCalcGrammar.cpp)
add_custom_command(TARGET AstAsmParser POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_SOURCE_DIR}/07-ast-asm-parser/ParseCalcGrammar.h
        COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_SOURCE_DIR}/07-ast-asm-parser/ParseCalcGrammar.cpp
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/07-ast-asm-parser)