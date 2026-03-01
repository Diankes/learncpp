#include <iostream>

int getUserInteger()
{
    std::cerr << "getUserInteger() called!\n";
    std::cout << "Enter a number: ";
    int x{};
    std::cin >> x;
    return x;
}

int main()
{
    std::cerr << "main() called!\n";
    int x{getUserInteger()};
    std::cout << "You entered: " << x << '\n';

    return 0;
}
