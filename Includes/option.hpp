#ifndef OPTION_H
#define OPTION_H

#include <cstddef>

#include "enums.hpp"
namespace Option
{
void ToggleOption(std::size_t op);
bool CheckOption(OptionEnum op);
}  // namespace Option

#endif