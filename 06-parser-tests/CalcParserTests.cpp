#include <catch.hpp>
#include "CalcParser.h"

class CreatedParserFixture
{
protected:
    void CheckCalculationResult(std::string const& sources, double expected)
    {
        const double result = GetResult(sources);
        REQUIRE(expected - result < std::numeric_limits<double>::epsilon());
    }

    void CheckCalculationThrows(std::string const& sources)
    {
        REQUIRE_THROWS_AS(GetResult(sources), std::runtime_error);
    }

private:
    double GetResult(std::string const& sources)
    {
        return parser.Calculate(sources);
    }

    CalcParser parser;
};

TEST_CASE_METHOD(CreatedParserFixture, "Returns error when wrong expression", "[CalcParser]")
{
    CheckCalculationThrows(";");
    CheckCalculationThrows("1");
    CheckCalculationThrows("/;");
    CheckCalculationThrows("undefined_variable;");
    CheckCalculationThrows("some;expression_without_semicolon");
    CheckCalculationThrows("1wrong_variable;");
    CheckCalculationThrows("wrong_expression=1&2;");
    CheckCalculationThrows("wrong_grammar=2++2");
    CheckCalculationThrows("(2+2");
    CheckCalculationThrows("2+2)");
}

TEST_CASE_METHOD(CreatedParserFixture, "Returns zero when parse empty string", "[CalcParser]")
{
    CheckCalculationResult("", 0.0);
}

TEST_CASE_METHOD(CreatedParserFixture, "Can calculate single expression", "[CalcParser]")
{
    CheckCalculationResult("2;", 2.0);
    CheckCalculationResult("3.14;", 3.14);

    CheckCalculationResult("(42);", 42);
    CheckCalculationResult("((42));", 42);
    CheckCalculationResult("(((42)));", 42);
}

TEST_CASE_METHOD(CreatedParserFixture, "Can calculate arithmetic expressions", "[CalcParser]")
{
    CheckCalculationResult("2+3;", 5.0);
    CheckCalculationResult("2-1;", 1.0);
    CheckCalculationResult("2*3;", 6.0);
    CheckCalculationResult("2/4;", 0.5);
}

TEST_CASE_METHOD(CreatedParserFixture, "Can calculate multiple operations", "[CalcParser]")
{
    CheckCalculationResult("6/3*2/4+2-1+2-3;", 1.0);
}

TEST_CASE_METHOD(CreatedParserFixture, "Can calculate in right arithmetical order", "[CalcParser]")
{
    CheckCalculationResult("2+2*2;", 6.0);
    CheckCalculationResult("2-2*2;", -2.0);
    CheckCalculationResult("5-2*2;", 1.0);
    CheckCalculationResult("5-2/2;", 4.0);

    CheckCalculationResult("(2+2)*2;", 8.0);
    CheckCalculationResult("(2-2)*2;", 0.0);
    CheckCalculationResult("(5-2)*2;", 6.0);
    CheckCalculationResult("(5-2)/2;", 1.5);
    CheckCalculationResult("3-14/(2+5)-(5-2)/2;", -0.5);
}

TEST_CASE_METHOD(CreatedParserFixture, "Can calculate multiple expressions", "[CalcParser]")
{
    CheckCalculationResult("2;3;", 3.0);
    CheckCalculationResult("2;3;4;5;", 5.0);
}

TEST_CASE_METHOD(CreatedParserFixture, "Can assign variables", "[CalcParser]")
{
    CheckCalculationResult("a=2;", 2.0);
    CheckCalculationResult("b=2;b;", 2.0);
    CheckCalculationResult("c=2;c;3;", 3.0);
    CheckCalculationResult("d=2+2*2;d;", 6.0);
    CheckCalculationResult("e=4;e=3.14;", 3.14);
    CheckCalculationResult("f=4;f=3.14;f;", 3.14);
}

TEST_CASE_METHOD(CreatedParserFixture, "Can use variables in expressions", "[CalcParser]")
{
    CheckCalculationResult("stupid_expression=2+2*2;stupid_expression+2;", 8.0);
    CheckCalculationResult("pi=3.14159;radius=42;area=2*pi*radius*radius;area;", 11083.5295);
}