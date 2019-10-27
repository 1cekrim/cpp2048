#include "option.hpp"
#include "enums.hpp"

#include <cstddef>
#include <iostream>

inline std::size_t option = 0;

void Option::ToggleOption(std::size_t op)
{
    option ^= 1LL << static_cast<std::size_t>(op - 1);
}

bool Option::CheckOption(OptionEnum op)
{
    return ((option & (1LL << (static_cast<std::size_t>(op) - 1))) != 0);
}