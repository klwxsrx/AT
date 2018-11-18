cmake_minimum_required(VERSION 3.12)
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
add_executable(ManualParserTests 06-parser-tests/CalcParserTests.cpp 06-parser-tests/main.cpp)
target_link_libraries(ManualParserTests Catch2 ManualParser)

### LEMON GENERATE PARSER ###
add_custom_target(LemonGenerateParser
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/lib/lemon/lempar.c ${CMAKE_BINARY_DIR}/lempar.c
        COMMAND Lemon 05-third-party-parser/ParserGrammar.y
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

### THIRD PARTY PARSER ###
add_library(ThirdPartyParser INTERFACE) # TODO: make cpp wrapper
target_include_directories(ManualParser PUBLIC 05-third-party-parser)
add_dependencies(ThirdPartyParser LemonGenerateParser)