#include <iostream>
#define ENABLE_DEBUG // Comment to disable debugging

int getUserInteger()
{
#ifdef ENABLE_DEBUG
    std::cerr << "getUserInteger() called!\n";
#endif
    std::cout << "Enter a number: ";
    int x{};
    std::cin >> x;
    return x;
}

int main()
{
#ifdef ENABLE_DEBUG
    std::cerr << "main() called!\n";
#endif
    int x{getUserInteger()};
    std::cout << "You entered: " << x << '\n';

    return 0;
}
