#ifndef GAME_H
#define GAME_H

#include "board.hpp"

#include <iosfwd>
#include <vector>

namespace Game
{
class Game
{
 public:
    Game(std::size_t height, std::size_t width);
    void DrawBoard(std::ostream& os) const;
    bool CreateBlockRandomPosition();
    void StartLoop();
    bool MainLoopDo();
    void GetKeyAndDoAction();

 private:
    std::size_t m_height, m_width;
    Board::Board m_board;
};
}  // namespace Game

#endif