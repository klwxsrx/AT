#pragma once

#include <stdexcept>
#include <map>
#include "ICalcParser.h"
#include "LemonToken.h"

class CalcParser final : public ICalcParser {
public:
    double Calculate(std::string const& source) override;

    double GetIdValue(const char *id) const;
    void SetIdValue(const char *id, double value);
    void SetResult(double result);
    void OnError(LemonToken const& token);
    void OnStackOverflow();

private:
    std::map<std::string, double> m_variables;
    double m_result = 0;
};