#include <iostream>
#include <stdlib.h>

// 4 functions for the 4 operators, +, -, *, /. Each accepting 2 parameters and returning the result
float add(float param1, float param2) { return param1 + param2; }

float subtract(float param1, float param2) { return param1 - param2; }

float multiply(float param1, float param2) { return param1 * param2; }

float divide(float param1, float param2) { return param1 / param2; }

int main()
{
    bool restart;
    float num1, num2;
    std::string chosenOp, tryAgain;

    do {
        restart = false;
        std::cout << "This is a calculator, input 2 numbers to get started!\n";
        std::cout << "First number: " ; std::cin >> num1;
        std::cout << "Second number: " ; std::cin >> num2;
        std::cout << "Which operator do you want to use? (+, -, *, /): "; std::cin >> chosenOp;

        // Depending on which operator user has chosen, calls the respective function and prints out the result for it
        if (chosenOp == "+") {
            std::cout << "The sum of the 2 numbers is: " << add(num1, num2) << "\n";
        } else if (chosenOp == "-") {
            std::cout << "The difference between the 2 numbers is: " << subtract(num1, num2) << "\n";
        } else if (chosenOp == "*") {
            std::cout << "The multiplication of the numbers is: " << multiply(num1, num2) << "\n";
        } else if (chosenOp == "/") {
            if (num2 != 0) {
                std::cout << "The division of the 2 numbers is: " << divide(num1, num2) << "\n";
            } else {
                std::cout << "Error: Division by zero is not allowed.\n";
            }
        } else {
            std::cout << "The input you have entered is invalid.\n";
        }

        // Clears the screen if user continues, exits the code if not continuing
        std::cout << "Would you like to try again? (y/n): " ; std::cin >> tryAgain;
        if (tryAgain == "y") {
            system("cls");
            restart = true;
        }
    } while (restart);

    return 0;
}
