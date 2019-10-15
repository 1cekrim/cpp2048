#ifndef OPTION_H
#define OPTION_H

#include "enums.hpp"

#include <cstddef>
#include <iostream>

namespace Option
{
static std::size_t option;
void ToggleOption(std::size_t op)
{
    Option::option ^= 1LL << static_cast<std::size_t>(op - 1);
}
}  // namespace Option

#endif