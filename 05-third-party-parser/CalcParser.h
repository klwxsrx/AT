#pragma once
#include <stdexcept>
#include "ICalcParser.h"
#include "LemonToken.h"

class CalcParser final : public ICalcParser {
public:
    double Calculate(std::string const& source) override;

    void OnError(LemonToken const& token);
    void OnStackOverflow();
};