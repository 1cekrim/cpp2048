#include "board.hpp"
#include "score.hpp"

#include <deque>
#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace Board
{
Block::Block()
{
    Init();
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

void Block::Init()
{
    std::size_t r = Random::get<std::size_t>(0, 99);
    if (r < 10)
    {
        m_level = 2;
    }
    else
    {
        m_level = 1;
    }
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

bool Board::CanMoveBlocks() const
{
    for (auto& block : m_board)
    {
        if (block == nullptr)
        {
            return true;
        }
    }

    return false;
}

ObjectPool<Block>& Board::GetObjectPool()
{
    return m_pool;
}

void Board::SetBoardBlock(std::size_t y, std::size_t x, Block* block)
{
    m_board[PositionToIdx(y, x)] = block;
}

bool Board::MoveBlocks(Dir dir, Score::Score& score)
{
    bool isColumn = dir == Dir::DOWN || dir == Dir::UP;
    bool isReverse = dir == Dir::DOWN || dir == Dir::RIGHT;

    auto absorbVector = [this, isReverse, &score](std::stack<Block*>& vector) {
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
            if (!isReverse)
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

            if (!isReverse)
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
                score.AddScore(lp->GetNumber());
                result.push_back(lp);
                lp = nullptr;
                continue;
            }
            else if (lp != nullptr)
            {
                result.push_back(lp);
            }
            lp = rp;
        }

        if (lp != nullptr)
        {
            result.push_back(lp);
        }

        for (auto i = result.rbegin(); i != result.rend(); ++i)
        {
            vector.push(*i);
        }
    };

    auto func = [this, isColumn](std::size_t idx) {
        return isColumn ? GetColumnVector(idx) : GetRowVector(idx);
    };

    std::vector<Block*> origin{ m_board };

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

    for (std::size_t i = 0; i < origin.size(); ++i)
    {  
        if (origin[i] != m_board[i]) 
        {
            return true;
        }
    }

    return false;
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