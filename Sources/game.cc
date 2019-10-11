#include "game.hpp"
#include "screen.hpp"

#include <cmath>
#include <iomanip>
#include <string>
#include <vector>

namespace Game
{
Game::Game(std::size_t height, std::size_t width)
    : m_height(height), m_width(width), m_board(height, width)
{
    // Do nothing.
}

void Game::DrawBoard(std::ostream& os) const
{
    using namespace Screen::Color;

    const std::vector<Board::Block*>& blocks = m_board.GetBoard();

    auto blankNumber = [&os](std::size_t number) {
        for (std::size_t i = 0; i < number; ++i)
        {
            os << " ";
        }
    };

    static const std::vector<Modifier*> blockColor = {
        &bgBlack,       &bgRed,          &bgGreen,      &bgYellow,
        &bgBlue,        &bgMagenta,      &bgBrightCyan, &bgBrightRed,
        &bgBrightGreen, &bgBrightYellow, &bgBrightBlue, &bgBrightMagenta,
        &bgBrightCyan,
    };

    os << bgWhite;
    blankNumber(6 * m_board.GetWidth() + 4);
    os << '\n';

    for (std::size_t y = 0; y < m_board.GetHeight(); ++y)
    {
        std::vector<std::size_t> nums;

        for (std::size_t x = 0; x < m_board.GetWidth(); ++x)
        {
            if (Board::Block* block = blocks.at(m_board.PositionToIdx(y, x));
                block == nullptr)
            {
                nums.push_back(1);
            }
            else
            {
                nums.push_back(block->GetNumber());
            }
        }

        for (std::size_t j = 0; j < 3; ++j)
        {
            os << bgWhite << "  ";
            for (auto& num : nums)
            {
                if (j == 0 || j == 2 || num == 1)
                {
                    os << *blockColor[static_cast<std::size_t>(std::log2(num))];
                    blankNumber(6);
                }
                else
                {
                    os << *blockColor[static_cast<std::size_t>(std::log2(num))];
                    blankNumber(4 - static_cast<std::size_t>(std::log10(num)));
                    os << fgWhite << std::to_string(num) << " ";
                }
            }
            os << bgWhite << "  ";
            os << '\n';
        }
    }
    os << bgWhite;
    blankNumber(6 * m_board.GetWidth() + 4);

    os << gmReset << '\n';
}

void Game::CreateBlockRandomPosition()
{
    m_board.CreateBlockRandomPosition();
}

}  // namespace Game