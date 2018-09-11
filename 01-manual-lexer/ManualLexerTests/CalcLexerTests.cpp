#include "../../lib/catch2/catch.hpp"
#include "../ManualLexer/CalcLexer.h"
#include <vector>

using namespace std;
using namespace calc;

namespace calc
{
bool operator==(const Token &a, const Token &b)
{
    return a.type == b.type && a.value == b.value;
}

string GetTokenName(TokenType type)
{
    switch (type) {
        case calc::TT_END: return "end";
        case calc::TT_ERROR: return "error";
        case calc::TT_NUMBER: return "number";
        case calc::TT_PLUS: return "+";
        default:return "<UNEXPECTED!!!>";
    }
}

std::ostream &operator<<(std::ostream &stream, const Token &token)
{
    stream << "Token(" << GetTokenName(token.type);
    if (token.value) {
        stream << ", " << *token.value;
    }
    stream << ")";
    return stream;
}
}

namespace
{

using TokenList = vector<Token>;

TokenList Tokenize(string text)
{
    TokenList results;
    CalcLexer lexer{text};
    for (Token token = lexer.Read(); token.type != TT_END; token = lexer.Read()) {
        results.emplace_back(move(token));
    }
    return results;
}

}

TEST_CASE("Can read one number", "[CalcLexer]")
{
    REQUIRE(Tokenize("0") == TokenList{
        Token{TT_NUMBER, "0"},
    });
    REQUIRE(Tokenize("1") == TokenList{
        Token{TT_NUMBER, "1"},
    });
    REQUIRE(Tokenize("9876543210") == TokenList{
        Token{TT_NUMBER, "9876543210"},
    });
    REQUIRE(Tokenize("00") == TokenList{
        Token{TT_ERROR},
    });
    REQUIRE(Tokenize("01") == TokenList{
        Token{TT_ERROR},
    });
    REQUIRE(Tokenize("0123") == TokenList{
        Token{TT_ERROR},
    });
    REQUIRE(Tokenize(".") == TokenList{
        Token{TT_ERROR},
    });
    REQUIRE(Tokenize("..") == TokenList{
        Token{TT_ERROR},
    });
    REQUIRE(Tokenize(".1") == TokenList{
        Token{TT_ERROR},
    });
    REQUIRE(Tokenize("00.1") == TokenList{
        Token{TT_ERROR},
    });
    REQUIRE(Tokenize("01.1") == TokenList{
        Token{TT_ERROR},
    });
    REQUIRE(Tokenize("0..1") == TokenList{
        Token{TT_ERROR},
    });
    REQUIRE(Tokenize("0.1.1") == TokenList{
        Token{TT_ERROR},
    });
    REQUIRE(Tokenize("0.") == TokenList{
        Token{TT_ERROR},
    });
    REQUIRE(Tokenize("0..") == TokenList{
        Token{TT_ERROR},
    });
    REQUIRE(Tokenize("0.00") == TokenList{
        Token{TT_NUMBER, "0.00"},
    });
    REQUIRE(Tokenize("0.0") == TokenList{
        Token{TT_NUMBER, "0.0"},
    });
    REQUIRE(Tokenize("1.0") == TokenList{
        Token{TT_NUMBER, "1.0"},
    });
    REQUIRE(Tokenize("123.0") == TokenList{
        Token{TT_NUMBER, "123.0"},
    });
    REQUIRE(Tokenize("123.400") == TokenList{
        Token{TT_NUMBER, "123.400"},
    });
    REQUIRE(Tokenize("0.1") == TokenList{
        Token{TT_NUMBER, "0.1"},
    });
    REQUIRE(Tokenize("0.123") == TokenList{
        Token{TT_NUMBER, "0.123"},
    });
    REQUIRE(Tokenize("123.456") == TokenList{
        Token{TT_NUMBER, "123.456"},
    });
}

TEST_CASE("Can read one operator", "[CalcLexer]")
{
    REQUIRE(Tokenize("+") == TokenList{
        Token{TT_PLUS},
    });
    REQUIRE(Tokenize("-") == TokenList{
        Token{TT_MINUS},
    });
    REQUIRE(Tokenize("*") == TokenList{
        Token{TT_MULT},
    });
    REQUIRE(Tokenize("/") == TokenList{
        Token{TT_DIV},
    });
}

TEST_CASE("Can read expression tokens", "[CalcLexer]")
{
    REQUIRE(Tokenize("45+9+28-7-4-22*0*2*4/5/78/1") == TokenList{
        Token{TT_NUMBER, "45"},
        Token{TT_PLUS},
        Token{TT_NUMBER, "9"},
        Token{TT_PLUS},
        Token{TT_NUMBER, "28"},
        Token{TT_MINUS},
        Token{TT_NUMBER, "7"},
        Token{TT_MINUS},
        Token{TT_NUMBER, "4"},
        Token{TT_MINUS},
        Token{TT_NUMBER, "22"},
        Token{TT_MULT},
        Token{TT_NUMBER, "0"},
        Token{TT_MULT},
        Token{TT_NUMBER, "2"},
        Token{TT_MULT},
        Token{TT_NUMBER, "4"},
        Token{TT_DIV},
        Token{TT_NUMBER, "5"},
        Token{TT_DIV},
        Token{TT_NUMBER, "78"},
        Token{TT_DIV},
        Token{TT_NUMBER, "1"},
    });

    REQUIRE(Tokenize("5+7.005+5") == TokenList{
        Token{TT_NUMBER, "5"},
        Token{TT_PLUS},
        Token{TT_NUMBER, "7.005"},
        Token{TT_PLUS},
        Token{TT_NUMBER, "5"},
    });

    REQUIRE(Tokenize("1.005-43.54/1") == TokenList{
        Token{TT_NUMBER, "1.005"},
        Token{TT_MINUS},
        Token{TT_NUMBER, "43.54"},
        Token{TT_DIV},
        Token{TT_NUMBER, "1"},
    });
    REQUIRE(Tokenize("1..005+43.54*1") == TokenList{
        Token{TT_ERROR},
        Token{TT_PLUS},
        Token{TT_NUMBER, "43.54"},
        Token{TT_MULT},
        Token{TT_NUMBER, "1"},
    });
    REQUIRE(Tokenize("1./43.54-1") == TokenList{
        Token{TT_ERROR},
        Token{TT_DIV},
        Token{TT_NUMBER, "43.54"},
        Token{TT_MINUS},
        Token{TT_NUMBER, "1"},
    });
}

TEST_CASE("Can read one operator with whitespaces", "[CalcLexer]")
{
    REQUIRE(Tokenize("  +") == TokenList{
        Token{TT_PLUS},
    });
    REQUIRE(Tokenize("\t+") == TokenList{
        Token{TT_PLUS},
    });
    REQUIRE(Tokenize("   \t\t+") == TokenList{
        Token{TT_PLUS},
    });
    REQUIRE(Tokenize("\n+") == TokenList{
        Token{TT_PLUS},
    });
    REQUIRE(Tokenize("   \n  +") == TokenList{
        Token{TT_PLUS},
    });
    REQUIRE(Tokenize("\t   \n  +") == TokenList{
        Token{TT_PLUS},
    });
    REQUIRE(Tokenize("+    ") == TokenList{
        Token{TT_PLUS},
    });
    REQUIRE(Tokenize("+  \t\t   ") == TokenList{
        Token{TT_PLUS},
    });
    REQUIRE(Tokenize("+  \n\t   ") == TokenList{
        Token{TT_PLUS},
    });
    REQUIRE(Tokenize("   +   ") == TokenList{
        Token{TT_PLUS},
    });
    REQUIRE(Tokenize("  \t +  \t ") == TokenList{
        Token{TT_PLUS},
    });
    REQUIRE(Tokenize("  \t\t +  \t ") == TokenList{
        Token{TT_PLUS},
    });
    REQUIRE(Tokenize("  \t \t +  \n\t ") == TokenList{
        Token{TT_PLUS},
    });
}

TEST_CASE("Can read one number with whitespaces", "[CalcLexer]")
{

    REQUIRE(Tokenize("  1") == TokenList{
        Token{TT_NUMBER, "1"},
    });
    REQUIRE(Tokenize("\t4") == TokenList{
        Token{TT_NUMBER, "4"},
    });
    REQUIRE(Tokenize("   \t\t3.2") == TokenList{
        Token{TT_NUMBER, "3.2"},
    });

    REQUIRE(Tokenize("\n9") == TokenList{
        Token{TT_NUMBER, "9"},
    });

    REQUIRE(Tokenize("   \n  15") == TokenList{
        Token{TT_NUMBER, "15"},
    });

    REQUIRE(Tokenize("\t   \n  21.03") == TokenList{
        Token{TT_NUMBER, "21.03"},
    });

    REQUIRE(Tokenize("0    ") == TokenList{
        Token{TT_NUMBER, "0"},
    });
    REQUIRE(Tokenize("81  \t\t   ") == TokenList{
        Token{TT_NUMBER, "81"},
    });
    REQUIRE(Tokenize("4.2  \n\t   ") == TokenList{
        Token{TT_NUMBER, "4.2"},
    });

    REQUIRE(Tokenize("   7.9   ") == TokenList{
        Token{TT_NUMBER, "7.9"},
    });
    REQUIRE(Tokenize("  \t 3  \t ") == TokenList{
        Token{TT_NUMBER, "3"},
    });
    REQUIRE(Tokenize("  \t\t 9.001  \t ") == TokenList{
        Token{TT_NUMBER, "9.001"},
    });
    REQUIRE(Tokenize("  \t \t 7  \n\t ") == TokenList{
        Token{TT_NUMBER, "7"},
    });

}

TEST_CASE("Can read expression tokens with whitespaces")
{
    REQUIRE(Tokenize("2 + 3") == TokenList{
        Token{TT_NUMBER, "2"},
        Token{TT_PLUS},
        Token{TT_NUMBER, "3"},
    });
    REQUIRE(Tokenize("\t0.52 + \n4") == TokenList{
        Token{TT_NUMBER, "0.52"},
        Token{TT_PLUS},
        Token{TT_NUMBER, "4"},
    });
    REQUIRE(Tokenize("\n+ \t7.1") == TokenList{
        Token{TT_PLUS},
        Token{TT_NUMBER, "7.1"},
    });
}
