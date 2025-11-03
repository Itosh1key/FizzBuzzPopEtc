#include "ErrorHandling.h"
#include <cassert>
#include <iostream>
#include <string_view>
#include <vector>

namespace AboutProgram {
    std::string name { "FizzBuzzPopEtc" };
    std::string author { "Itosh1key" };
    std::string version { "1.0.0" };

    void print()
    {
        std::cout << name << " v" << version << '\n'
                  << "By " << author << "\n\n";
    }
} // namespace AboutProgram

// This namespace handles the user input and input validation.
namespace UserInput {
    int countTo()
    {
        while (true) {
            std::cout << "How many iterations?\n";
            int count {};
            std::cout << '>';
            std::cin >> count;

            if (ErrorHandling::clearFailedExtraction()) {
                std::cout << "\nError: Invalid input. Try again.\n";
                continue;
            }

            ErrorHandling::ignoreLine();

            return count;
        }
    }

    int getUserChoice()
    {
        int choice {};
        do {
            std::cout << "1) FizzBuzz\n"
                      << "2) FizzBuzzPop\n"
                      << "3) FizzBuzzPopEtc v2.0\n";

            std::cout << '>';
            std::cin >> choice;

            if (ErrorHandling::clearFailedExtraction()) {
                std::cout << "\nError: Invalid input. Try again.\n\n";
                continue;
            }

            ErrorHandling::ignoreLine();

        } while ((choice < 1) || (choice > 3));

        return choice;
    }

    bool tryAgain()
    {
        while (true) {
            char c {};
            std::cout << "\nTry again? (y/n) ";
            std::cin >> c;

            if (!ErrorHandling::clearFailedExtraction())
                ErrorHandling::ignoreLine();

            switch (c) {
            case 'y':
                return true;
            case 'n':
                return false;
            default:
                std::cout << "\nError: Invalid input. Try again.\n";
            }
        }
    }
} // namespace UserInput

// Simple FizzBuzz
void fizzBuzz(int count)
{
    for (int iii { 1 }; iii <= count; ++iii) {
        if ((iii % 3 == 0) && (iii % 5 == 0))
            std::cout << "fizzbuzz\n";
        else if (iii % 3 == 0)
            std::cout << "fizz\n";
        else if (iii % 5 == 0)
            std::cout << "buzz\n";
        else
            std::cout << iii << '\n';
    }
}

// FizzBuzz, but with Pop
void fizzBuzzpop(int count)
{
    for (int jjj { 1 }; jjj <= count; ++jjj) {
        bool printed { false };
        if (jjj % 3 == 0) {
            std::cout << "fizz";
            printed = true;
        }
        if (jjj % 5 == 0) {
            std::cout << "buzz";
            printed = true;
        }
        if (jjj % 7 == 0) {
            std::cout << "pop";
            printed = true;
        }
        if (!printed)
            std::cout << jjj;

        std::cout << '\n';
    }
}

// FizzBuzzPopEtc
void fizzBuzzpopEtc(int count)
{
    using namespace std::literals; // for sv literals

    // We'll make these static so we only have to do initialization once
    static const std::vector divisors { 3, 5, 7, 11, 13, 17, 19 };
    static const std::vector words 
        { "fizz"sv, "Buzz"sv, "pop"sv, "bang"sv, "jazz"sv, "pow"sv, "boom"sv };

    assert(std::size(divisors) == std::size(words) && 
        "fizzBuzzEtc: array sizes don't match");

    // Loop through each number between 1 and count (inclusive)
    for (int iii { 1 }; iii <= count; ++iii) {
        bool printed { false };

        // Check the current number against each possible divisor
        for (std::size_t jjj { 0 }; jjj < divisors.size(); ++jjj) {
            if (iii % divisors[jjj] == 0) {
                std::cout << words[jjj];
                printed = true;
            }
        }

        // If there were no divisors
        if (!printed)
            std::cout << iii;

        std::cout << '\n';
    }
}

void selectOption(int choice, int count)
{
    switch (choice) {
    case 1:
        fizzBuzz(count);
        break;
    case 2:
        fizzBuzzpop(count);
        break;
    case 3:
        fizzBuzzpopEtc(count);
        break;
    }
}

int main()
{
    AboutProgram::print();

    do {
        int choice { UserInput::getUserChoice() };
        int count { UserInput::countTo() };

        selectOption(choice, count);
    } while (UserInput::tryAgain());
}