#ifndef MAZIAKCOORDINAT_H
#define MAZIAKCOORDINAT_H

#include <utility>

namespace ribi {
namespace maziak {

using Coordinat = std::pair<int, int>;

constexpr int col_index(const Coordinat c) noexcept { return c.first; }
constexpr int row_index(const Coordinat c) noexcept { return c.second; }
constexpr int x(const Coordinat c) noexcept { return c.first; }
constexpr int y(const Coordinat c) noexcept { return c.second; }

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKCOORDINAT_H
