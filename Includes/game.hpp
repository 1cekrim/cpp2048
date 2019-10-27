#ifndef GAME_H
#define GAME_H

#include "board.hpp"
#include "score.hpp"

#include <iosfwd>
#include <vector>
#include <string>

namespace Game
{
class Game
{
 public:
    Game(std::size_t height, std::size_t width);
    void DrawBoard(std::ostream& os) const;
    std::string DrawScore() const;
    bool CreateBlockRandomPosition();
    void StartLoop();
    bool MainLoopDo();
    bool GetKeyAndDoAction();
    bool CanMoveBlocks() const;

 private:
    std::size_t m_height, m_width;
    Score::Score m_score;
    Board::Board m_board;
};
}  // namespace Game

#endif