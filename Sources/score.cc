#include "score.hpp"

namespace Score
{
void Score::AddScore(std::size_t score)
{
    m_score += score;
}

std::size_t Score::GetScore() const
{
    return m_score;
}
}  // namespace Score