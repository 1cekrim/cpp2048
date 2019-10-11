#include "menu.hpp"
#include "game.hpp"
#include "screen.hpp"

#include <iostream>
#include <sstream>

using namespace Screen;
using namespace Image;

namespace Menu
{
void DrawMainMenuChoice(std::ostream& os)
{
    const std::vector<std::string> choice = { "1. Start Game",
                                              "2. View Highscore", "3. exit" };
    constexpr auto indent = "        ";

    os << '\n' << Color::gmBoldOn;

    for (auto& s : choice)
    {
        os << indent << s << '\n';
    }

    os << Color::gmReset;
}

void DrawMainMenu()
{
    ClearScreen();

    std::ostringstream menu;
    menu << LogoImage();
    DrawMainMenuChoice(menu);

    std::cout << menu.str();
}

void MainMenu()
{
    while (true)
    {
        DrawMainMenu();

        int choice;
        choice = GetKey();

        switch (choice)
        {
            case '1':
                StartGame();
            case '2':
                break;
            case '3':
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
    game.CreateBlockRandomPosition();
    game.DrawBoard(std::cout);
    Screen::PauseGameUntilPressEnter();
}
}  // namespace Menu
