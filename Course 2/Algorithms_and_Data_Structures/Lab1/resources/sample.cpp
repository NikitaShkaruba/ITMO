#include <iostream>
#include <string>

// Input file to the main program.
int main() {
    int i = 100500;
    std::string greetings = "Hello World!";
    int* ptr = new int;

    std::cout << greetings << i << *ptr;
}