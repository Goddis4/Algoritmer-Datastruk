#include <iostream>

double cNumber = 1;
double lNumber = 0;
double nNumber;


int recurFactorial(double number)
{
    double solution;
    double s1;

    // Setting a base    
    if (number == 1 || number == 0) {
        solution = 1;
    }
    else {
        s1 = recurFactorial(number - 1);
        solution = number * s1;
    }
    return solution;
}

int recurFibonacci(double length)
{

    nNumber = cNumber + lNumber;
    std::cout << nNumber << std::endl;
    lNumber = cNumber;
    cNumber = nNumber;

    if (length > 2) {
        recurFibonacci(length - 1);
    }
    return cNumber;
}

int main()
{
    double factorialInput; // This number will be user input for the factorial
    double fibonacciInput; // This number will be user input for the fibonacci

    std::cout << "Write a number and press enter:\n";
    std::cin >> factorialInput;

    double result = recurFactorial(factorialInput);
    std::cout << "Factorial of " << factorialInput << " is " << result << "\n";

    std::cout << "Write a number and press enter:\n";
    std::cin >> fibonacciInput;
    if (!std::cin) {
        std::cout << "Dont work" << std::endl;
    }
    else {
        std::cout << "A " << fibonacciInput << " long Fibonacci sequence is:\n" << "1\n";
        recurFibonacci(fibonacciInput);
    }

    return 0;
}
