#include "screen.hpp"

#include <iostream>

using namespace Screen;
using namespace Color;
using namespace Image;

int main(void)
{
    int a;
    ClearScreen();
    DrawFunc(std::cout, LogoImage);
    std::cin >> a; 
}