// ConsoleAppWithTests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

int main()
{
    double firstNum, secondNum;
    char _operator;

    do {
        std::cout << "Please enter a number:";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> firstNum;
    } while (!(std::cin >> firstNum));

    std::cout << "Please enter another number:";
    std::cin >> secondNum;

    std::cout << "Please enter operator";
    std::cin >> _operator;

    std::string validOperators = "+-*/";
    if (validOperators.find(_operator) == -1) {
        std::cout << "Unknown operator";
        return 0;
    }


    double result = 0;
    switch (_operator) {
    case '+':
        result = firstNum + secondNum;
        break;
    case '-':
        result = firstNum - secondNum;
        break;
    case '*':
        result = firstNum * secondNum;
        break;
    case '/':
        result = firstNum / secondNum;
        break;
    }

    std::cout << result;

}
