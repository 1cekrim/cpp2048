#include "board.hpp"

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace Board
{
Block::Block(std::size_t level) : m_level(level)
{
    // Do nothing.
}

bool Block::operator==(const Block& rhs) const
{
    return this->m_level == rhs.m_level;
}

std::size_t Block::GetNumber() const
{
    return 1LL << m_level;
}

void Block::SetLevel(std::size_t level)
{
    m_level = level;
}

Board::Board(std::size_t height, std::size_t width)
    : m_height(height), m_width(width), m_pool(height * width)
{
    m_board.resize(height * width, nullptr);
}

bool Board::CreateBlock(BlockIdx idx)
{
    auto& block = *idx;
    if (block != nullptr)
    {
        return false;
    }

    block = m_pool.Pop();
    return true;
}

bool Board::CreateBlockRandomPosition()
{
    std::vector<BlockIdx> list;

    for (auto i = m_board.begin(); i != m_board.end(); ++i)
    {
        if (*i == nullptr)
        {
            list.push_back(i);
        }
    }

    if (list.empty())
    {
        return false;
    }

    return CreateBlock(*Random::get(list));
}

void Board::MoveBlocks([[maybe_unused]] Dir dir)
{
    // pass
}

void Board::AbsorbBlocks([[maybe_unused]] BlockIdx target,
                         [[maybe_unused]] BlockIdx victim)
{
    // pass
}

const std::vector<Block*>& Board::GetBoard() const
{
    return m_board;
}

std::size_t Board::GetHeight() const
{
    return m_height;
}

std::size_t Board::GetWidth() const
{
    return m_width;
}

std::size_t Board::PositionToIdx(std::size_t y, std::size_t x) const
{
    return m_width * y + x;
}
}  // namespace Board