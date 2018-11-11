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

private:
    double GetResult(std::string const& sources)
    {
        return parser.Calculate(sources);
    }

    CalcParser parser;
};

TEST_CASE_METHOD(CreatedParserFixture, "Returns zero when parse empty string", "[CalcParser]")
{
    CheckCalculationResult("", 0.0);
}