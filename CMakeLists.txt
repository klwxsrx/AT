cmake_minimum_required(VERSION 3.12)
project(AT)

set(CMAKE_CXX_STANDARD 17)

### CATCH2 ###
add_library(Catch2 INTERFACE)
target_include_directories(Catch2 INTERFACE /lib/catch2)

### LEXERTL ###
add_library(Lexertl INTERFACE)
target_include_directories(Lexertl INTERFACE /lib/lexertl)

### COMMON ###
add_library(Common INTERFACE)
target_include_directories(Catch2 INTERFACE 00-common)

### MANUAL LEXER ###
add_library(ManualLexer 01-manual-lexer/CalcLexer.h 01-manual-lexer/CalcLexer.cpp)
target_include_directories(ManualLexer PUBLIC 01-manual-lexer 00-common)
target_link_libraries(ManualLexer Common)

### MANUAL LEXER TESTS ###
add_executable(ManualLexerTests 03-lexer-tests/CalcLexerTests.cpp 03-lexer-tests/main.cpp)
target_include_directories(ManualLexerTests PRIVATE lib/catch2)
target_link_libraries(ManualLexerTests Catch2 ManualLexer)

### THIRD PARTY LEXER ####
add_library(ThirdPartyLexer 02-third-party-lexer/CalcLexer.h 02-third-party-lexer/CalcLexer.cpp)
target_include_directories(ThirdPartyLexer PUBLIC lib/lexertl 02-third-party-lexer 00-common)
target_link_libraries(ThirdPartyLexer Common Lexertl)

### THIRD PARTY LEXER TESTS ###
add_executable(ThirdPartyLexerTests 03-lexer-tests/CalcLexerTests.cpp 03-lexer-tests/main.cpp)
target_include_directories(ThirdPartyLexerTests PRIVATE lib/catch2)
target_link_libraries(ThirdPartyLexerTests Catch2 ThirdPartyLexer)

### PARSER ###
add_library(Parser 04-parser/CalcParser.h 04-parser/CalcParser.cpp)
target_include_directories(Parser PUBLIC 04-parser)
target_link_libraries(Parser ManualLexer)