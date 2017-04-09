#include "maziakcoordinat.h"

#include <iostream>

std::vector<ribi::maziak::Coordinat>
ribi::maziak::get_adjacent_4(const Coordinat c) noexcept
{
  return
  {
    get_above(c),
    get_right(c),
    get_below(c),
    get_left(c)
  };
}

std::ostream& ribi::maziak::operator<<(std::ostream& os, const Coordinat& c) noexcept
{
  os << '(' << c.first << ", " << c.second << ')';
  return os;
}

