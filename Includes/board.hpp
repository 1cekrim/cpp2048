#ifndef BOARD_H
#define BOARD_H

#include <stack>
#include <vector>

namespace Board
{
class Block
{
 public:
    explicit Block(std::size_t level = 1);
    Block* Absorb(Block& block);

 private:
    std::size_t m_level;
    ObjectPool<Block>* m_pool;
};

class Board
{
 public:
    Board(std::size_t height, std::size_t width);
    void CreateBlock();
    constexpr std::size_t PositionToIdx(std::size_t y, std::size_t x);
    
 private:
    std::size_t m_height, m_width;
    std::vector<Block*> m_board;
};
}  // namespace Board

namespace Board
{
template <typename T, typename... Args>
class ObjectPool
{
    ObjectPool(std::size_t size, Args&& args)
    {
        objects.reserve(size);

        for (std::size_t i = 0; i < m_size; ++i)
        {
            T* object = new T(std::forward<Args>(args)...);
            object->ObjectPool = this;
            m_objects.push_back(object);
        }
    }

    ~ObjectPool()
    {
        while (!objects.empty())
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
        return ret;
    }

    void Push(T* object)
    {
        m_objects.push(object);
    }

    std::stack<T*> m_objects;
};
}  // namespace Board

#endif