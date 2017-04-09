#ifndef MAZIAKCOORDINAT_H
#define MAZIAKCOORDINAT_H

#include <utility>

namespace ribi {
namespace maziak {

using Coordinat = std::pair<int, int>;

constexpr int get_col(const Coordinat c) noexcept { return c.first; }
constexpr int get_row(const Coordinat c) noexcept { return c.second; }
constexpr int get_x(const Coordinat c) noexcept { return c.first; }
constexpr int get_y(const Coordinat c) noexcept { return c.second; }

constexpr Coordinat get_above(const Coordinat c) noexcept { return { c.first, c.second - 1}; }
constexpr Coordinat get_below(const Coordinat c) noexcept {return { c.first, c.second + 1}; }
constexpr Coordinat get_left(const Coordinat c) noexcept {return { c.first - 1, c.second }; }
constexpr Coordinat get_right(const Coordinat c) noexcept {return { c.first + 1, c.second }; }

///Get the four (vertical xor horizontal) adjacent coordinats
constexpr std::initializer_list<Coordinat> get_adjacent_4(const Coordinat c)
{
  return
  {
    get_above(c),
    get_right(c),
    get_below(c),
    get_left(c)
  };
}

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKCOORDINAT_H
