#ifndef SCORE_H
#define SCORE_H

#include <cstddef>

namespace Score
{
class Score
{
 public:
    std::size_t GetScore() const;
    void AddScore(std::size_t score);
 private:
    std::size_t m_score = 0;
};
}  // namespace Score
#endif