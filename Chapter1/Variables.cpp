#include <iostream>

int main()
{
    std::cout << 5 << std::endl;       // print literal number `5`
    std::cout << 11.2 << std::endl;    // print literal number `11.2`
    std::cout << 'X' << std::endl;     // print literal character `X`
    std::cout << "Hello" << std::endl; // print literal string `Hello`

    int x; // defining a variable identifier is `x`, data type is int
    x = 1;
    int width;
    width = 5 + x;
    std::cout << width << std::endl;
    width = 10;
    std::cout << width << std::endl;

    // default values with curly brackets
    float price{3.5};
    // using line break since it does not trigger flushing
    std::cout << price << '\n';
    int s{1};
    bool hasSize{false};
    char a{'A'};
    std::cout << s << '\n'
              << hasSize << '\n'
              << a << std::endl;

    // using expressions
    int y{s + x};
    int z{1 + 2 + 3};
    std::cout << y << z << '\n';

    return 0;
}
