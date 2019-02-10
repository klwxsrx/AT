#include <string>
#include <iostream>
#include <iomanip>
#include "CalcParser.h"

double HandleInput(CalcParser& parser)
{
    std::string inputString;
    std::getline(std::cin, inputString);

    return parser.Calculate(inputString);
}

int main()
{
    CalcParser parser;

    while (!std::cin.eof() && !std::cin.fail())
    {
        std::cout << "> " << std::setprecision(3);
        try
        {
            const double result = HandleInput(parser);
            std::cout << "Result: " << result;
        }
        catch (std::runtime_error const& e)
        {
            std::cout << "Error: " << e.what() << std::endl;
        }
        std::cout << std::endl;
    }
}