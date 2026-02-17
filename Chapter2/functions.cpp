#include <iostream>

void sayHello()
{
    std::cout << "Hello World" << std::endl;
}
int retrieveUserInput()
{
    int num{};
    std::cin >> num;
    return num;
}
int main()
{
    std::cout << "Looking through" << '\n';
    sayHello();
    std::cout << "functions" << '\n';
    std::cout << "Enter a number: " << '\n';
    int n{retrieveUserInput()};
    std::cout << "Your number times 3 is: " << n * 3 << std::endl;
    return 0;
}
