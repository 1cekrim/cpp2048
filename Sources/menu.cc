#include "menu.hpp"
#include "enums.hpp"
#include "game.hpp"
#include "option.hpp"
#include "screen.hpp"

#include <iostream>
#include <sstream>

using namespace Screen;
using namespace Image;

extern std::size_t option;

namespace Menu
{
void DrawMainMenuChoice(std::ostream& os)
{
    const std::vector<std::string> choice = {
        "1. Start Game", "2. View Highscore", "3. option", "4. exit"
    };
    constexpr auto indent = "        ";

    os << '\n' << Color::gmBoldOn;

    for (auto& s : choice)
    {
        os << indent << s << '\n';
    }

    os << Color::gmReset;
}

void DrawOptionMenuChoice(std::ostream& os,
                          const std::vector<std::string>& options)
{
    constexpr auto indent = "        ";

    os << '\n' << Color::gmBoldOn;
    std::size_t op = option;

    for (auto& s : options)
    {
        os << indent << s << " [ " << ((op % 2 == 1) ? "O" : " ") << " ]"
           << '\n';
        op >>= 1;
    }

    os << indent << options.size() + 1 << ". Return to main menu"
       << Color::gmReset << '\n';
}

void DrawOptionMenu(const std::vector<std::string>& options)
{
    ClearScreen();

    std::ostringstream menu;
    menu << LogoImage();
    DrawOptionMenuChoice(menu, options);

    std::cout << menu.str();
}

void DrawMainMenu()
{
    ClearScreen();

    std::ostringstream menu;
    menu << LogoImage();
    DrawMainMenuChoice(menu);

    std::cout << menu.str();
}

void OptionMenu()
{
    const std::vector<std::string> options = {
        "1. View scores during gameplay?",
        "2. Auto Save? (Not implemented yet)"
    };

    while (true)
    {
        DrawOptionMenu(options);

        int choice = GetKey() - '0';

        if (choice == options.size() + 1)
        {
            break;
        }

        if (choice > 0 && choice <= options.size())
        {
            Option::ToggleOption(choice);
        }
        else
        {
            std::cout << Color::bgRed << Color::fgWhite << "Wrong Input!\n"
                      << Color::gmReset;
            PauseGameUntilPressEnter();
        }
    }
}

void MainMenu()
{
    while (true)
    {
        DrawMainMenu();

        int choice = GetKey();

        switch (choice)
        {
            case '1':
                StartGame();
                break;
            case '2':
                break;
            case '3':
                OptionMenu();
                break;
            case '4':
                return;
            default:
                std::cout << Color::bgRed << Color::fgWhite << "Wrong Input!\n"
                          << Color::gmReset;
                PauseGameUntilPressEnter();
        }
    }
}

void StartGame()
{
    std::size_t n;
    std::cout << "Input board size n (n x n)" << '\n';
    std::cin >> n;
    std::cin.ignore(100, '\n');
    Game::Game game(n, n);
    game.StartLoop();
}
}  // namespace Menu
