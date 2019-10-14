#include "board.hpp"

#include <deque>
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

std::size_t Block::GetLevel() const
{
    return m_level;
}

Board::Board(std::size_t height, std::size_t width)
    : m_height(height), m_width(width), m_pool(height * width * 2)
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

ObjectPool<Block>& Board::GetObjectPool()
{
    return m_pool;
}

void Board::SetBoardBlock(std::size_t y, std::size_t x, Block* block)
{
    m_board[PositionToIdx(y, x)] = block;
}

void Board::MoveBlocks(Dir dir)
{
    bool isColumn = dir == Dir::DOWN || dir == Dir::UP;
    bool isReverse = dir == Dir::DOWN || dir == Dir::RIGHT;

    auto absorbVector = [this, isReverse](std::stack<Block*>& vector) {
        std::vector<Block*> result;
        std::deque<Block*> noZero;

        while (!vector.empty())
        {
            Block* block = vector.top();
            vector.pop();

            if (block != nullptr)
            {
                noZero.push_back(block);
            }
        }

        ObjectPool<Block>& pool = GetObjectPool();
        Block* lp = nullptr;

        if (!noZero.empty())
        {
            if (isReverse)
            {
                lp = noZero.back();
                noZero.pop_back();
            }
            else
            {
                lp = noZero.front();
                noZero.pop_front();
            }
        }

        while (!noZero.empty())
        {
            Block* rp;

            if (isReverse)
            {
                rp = noZero.back();
                noZero.pop_back();
            }
            else
            {
                rp = noZero.front();
                noZero.pop_front();
            }

            if (lp != nullptr && lp->GetLevel() == rp->GetLevel())
            {
                pool.Push(rp);
                lp->SetLevel(lp->GetLevel() + 1);
                vector.push(lp);
                lp = nullptr;
                continue;
            }
            else if (lp != nullptr)
            {
                vector.push(lp);
            }
            lp = rp;
        }

        if (lp != nullptr)
        {
            vector.push(lp);
        }
    };

    auto func = [this, isColumn](std::size_t idx) {
        return isColumn ? GetColumnVector(idx) : GetRowVector(idx);
    };

    for (std::size_t i = 0; i < (isColumn ? m_width : m_height); ++i)
    {
        std::stack<Block*> vec = func(i);
        absorbVector(vec);

        std::size_t size = isColumn ? m_height : m_width;
        std::size_t j = isReverse ? size - 1 : 0;

        while (true)
        {
            if ((isReverse && j == -1) || (!isReverse && j == size))
            {
                break;
            }

            Block* now = nullptr;

            if (!vec.empty())
            {
                now = vec.top();
                vec.pop();
            }

            if (isColumn)
            {
                SetBoardBlock(j, i, now);
            }
            else
            {
                SetBoardBlock(i, j, now);
            }

            if (isReverse)
            {
                --j;
            }
            else
            {
                ++j;
            }
        }
    }
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

std::stack<Block*> Board::GetColumnVector(std::size_t x)
{
    std::stack<Block*> result;

    for (std::size_t i = 0; i < m_height; ++i)
    {
        result.push(m_board[PositionToIdx(i, x)]);
    }

    return result;
}

std::stack<Block*> Board::GetRowVector(std::size_t y)
{
    std::stack<Block*> result;

    for (std::size_t i = 0; i < m_width; ++i)
    {
        result.push(m_board[PositionToIdx(y, i)]);
    }

    return result;
}
}  // namespace Board