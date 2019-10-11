#include "screen.hpp"

#include <cstdlib>
#include <iostream>
#include <map>
#include <sstream>
#include <string_view>
#include <vector>

#ifdef _WIN32
#include <conio.h>

void Screen::ClearScreen()
{
    system("cls");
}

int Screen::GetKey()
{
    return _getch();
}

void Screen::PauseGameUntilPressEnter()
{
    std::cout << "Press Enter key to continue..." << '\n';
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

#else

#include <termios.h>
#include <unistd.h>

void Screen::ClearScreen()
{
    system("clear");
}

int Screen::GetKey(void)
{
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

#endif

namespace Screen::Color
{
Modifier::Modifier(Code pCode) : code(pCode)
{
    // Do nothing.
}

std::ostream& operator<<(std::ostream& os, const Modifier& mod)
{
    return os << "\033[" << static_cast<int>(mod.code) << "m";
}
}  // namespace Screen::Color

namespace Screen::Image
{
std::string LogoImage()
{
    const ImageVector logoText = {
        "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC",
        "C                                 C",
        "C  RRRRR   YYYYY   G   G   BBBBB  C",
        "C      R   Y   Y   G   G   B   B  C",
        "C  RRRRR   Y   Y   GGGGG   BBBBB  C",
        "C  R       Y   Y       G   B   B  C",
        "C  RRRRR   YYYYY       G   BBBBB  C",
        "C                                 C",
        "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC",
    };
    return ImageToString(logoText);
}

std::string ImageToString(const ImageVector& image)
{
    static std::map<char, Color::Modifier&> colors{
        { ' ', Color::bgBlack }, { 'R', Color::bgRed },
        { 'G', Color::bgGreen }, { 'Y', Color::bgYellow },
        { 'B', Color::bgBlue },  { 'M', Color::bgMagenta },
        { 'C', Color::bgCyan },  { 'W', Color::bgWhite },
    };

    std::ostringstream imageStream;

    imageStream << colors.find(' ')->second;
    char lastColor = ' ';

    for (auto& str : image)
    {
        for (auto& color : str)
        {
            if (lastColor != color)
            {
                imageStream << colors.find(lastColor = color)->second;
            }
            imageStream << "  ";
        }
        imageStream << '\n';
    }

    imageStream << Color::gmReset;
    return imageStream.str();
}
}  // namespace Screen::Image