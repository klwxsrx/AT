#pragma once
#include <string>

class ICalcParser
{
public:
    virtual ~ICalcParser() = default;
    virtual double Calculate(std::string const& source) = 0;

};