#ifndef BOARD_H
#define BOARD_H

#include "enums.hpp"

#include <stack>
#include <vector>

namespace Board
{
template <typename T>
class ObjectPool
{
 public:
    ObjectPool(std::size_t size)
    {
        for (std::size_t i = 0; i < size; ++i)
        {
            T* object = new T();
            m_objects.push(object);
        }
    }

    ~ObjectPool()
    {
        while (!m_objects.empty())
        {
            T* object = m_objects.top();
            m_objects.pop();
            delete object;
        }
    }

    T* Pop()
    {
        T* ret = m_objects.top();
        m_objects.pop();
        ret->Init();
        return ret;
    }

    void Push(T* object)
    {
        m_objects.push(object);
    }

    std::stack<T*> m_objects;
};

class Block
{
 public:
    explicit Block();
    void SetLevel(std::size_t level);
    std::size_t GetLevel() const;
    bool operator==(const Block& rhs) const;
    std::size_t GetNumber() const;
    void Init();

 private:
    std::size_t m_level;
};

class Board
{
 public:
    using BlockIdx = std::vector<Block*>::iterator;

 public:
    Board(std::size_t height, std::size_t width);
    bool CreateBlock(BlockIdx idx);
    bool CreateBlockRandomPosition();
    void MoveBlocks(Dir dir);
    std::size_t GetHeight() const;
    std::size_t GetWidth() const;
    const std::vector<Block*>& GetBoard() const;
    void SetBoardBlock(std::size_t y, std::size_t x, Block* block);
    ObjectPool<Block>& GetObjectPool();
    std::size_t PositionToIdx(std::size_t y, std::size_t x) const;

    std::stack<Block*> GetColumnVector(std::size_t x);
    std::stack<Block*> GetRowVector(std::size_t y);

 private:
    std::size_t m_height, m_width;
    ObjectPool<Block> m_pool;
    std::vector<Block*> m_board;
};
}  // namespace Board

#endif