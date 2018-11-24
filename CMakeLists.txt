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

### MANUAL PARSER UI ###
add_executable(ManualParserUI 07-parser-ui/main.cpp)
target_link_libraries(ManualParserUI ManualParser)

### THIRD PARTY PARSER ###
add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/ParseCalcGrammar.h ${CMAKE_CURRENT_BINARY_DIR}/ParseCalcGrammar.cpp
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/lib/lemon/lempar.c ${CMAKE_BINARY_DIR}/
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/05-third-party-parser/* ${CMAKE_BINARY_DIR}/
        COMMAND Lemon -q -l -s ${CMAKE_BINARY_DIR}/ParseCalcGrammar.y
        COMMAND ${CMAKE_COMMAND} -E rename ${CMAKE_BINARY_DIR}/ParseCalcGrammar.c ${CMAKE_BINARY_DIR}/ParseCalcGrammar.cpp)
add_library(ThirdPartyParser
        05-third-party-parser/ICalcParser.h
        05-third-party-parser/LemonToken.h
        05-third-party-parser/CalcParser.h
        05-third-party-parser/CalcParser.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/ParseCalcGrammar.h
        ${CMAKE_CURRENT_BINARY_DIR}/ParseCalcGrammar.cpp)
        target_include_directories(ThirdPartyParser PUBLIC 05-third-party-parser)
target_link_libraries(ThirdPartyParser ManualLexer)