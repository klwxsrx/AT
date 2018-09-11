cmake_minimum_required(VERSION 3.12)
project(AT)

set(CMAKE_CXX_STANDARD 17)

add_library(ManualLexer
    01-manual-lexer/ManualLexer/Token.h
    01-manual-lexer/ManualLexer/CalcLexer.h
    01-manual-lexer/ManualLexer/CalcLexer.cpp
)

add_executable(ManualLexerTests
    lib/catch2/catch.hpp
    01-manual-lexer/ManualLexerTests/CalcLexerTests.cpp
    01-manual-lexer/ManualLexerTests/main.cpp
)
target_link_libraries(ManualLexerTests ManualLexer)