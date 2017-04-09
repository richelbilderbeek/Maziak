#ifndef MAZIAKCOORDINAT_H
#define MAZIAKCOORDINAT_H

#include <iosfwd>
#include <utility>
#include <vector>

namespace ribi {
namespace maziak {

using Coordinat = std::pair<int, int>;

constexpr int get_col(const Coordinat c) noexcept { return c.first; }
constexpr int get_row(const Coordinat c) noexcept { return c.second; }
constexpr int get_x(const Coordinat c) noexcept { return c.first; }
constexpr int get_y(const Coordinat c) noexcept { return c.second; }

constexpr Coordinat get_above(const Coordinat c) noexcept { return Coordinat(c.first, c.second - 1); }
constexpr Coordinat get_below(const Coordinat c) noexcept { return Coordinat(c.first, c.second + 1); }
constexpr Coordinat get_left(const Coordinat c) noexcept { return Coordinat(c.first - 1, c.second ); }
constexpr Coordinat get_right(const Coordinat c) noexcept { return Coordinat(c.first + 1, c.second ); }

///Get the four (vertical xor horizontal) adjacent coordinats
std::vector<Coordinat> get_adjacent_4(const Coordinat c) noexcept;

std::ostream& operator<<(std::ostream& os, const Coordinat& c) noexcept;

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKCOORDINAT_H
