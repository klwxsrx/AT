cmake_minimum_required(VERSION 3.12)
project(AT)

set(CMAKE_CXX_STANDARD 17)

### CATCH2 ###
add_library(Catch2 INTERFACE)
target_include_directories(Catch2 INTERFACE /lib/catch2)

### COMMON ###
add_library(Common INTERFACE)
target_include_directories(Catch2 INTERFACE /00-common)

### MANUAL LEXER ###
add_library(ManualLexer 01-manual-lexer/CalcLexer.h 01-manual-lexer/CalcLexer.cpp)
target_include_directories(ManualLexer PUBLIC 00-common)
target_link_libraries(ManualLexer Common)

### MANUAL LEXER TESTS ###
add_executable(ManualLexerTests 03-lexer-tests/CalcLexerTests.cpp 03-lexer-tests/main.cpp)
target_include_directories(ManualLexerTests PRIVATE lib/catch2 01-manual-lexer)
target_link_libraries(ManualLexerTests Catch2 ManualLexer)