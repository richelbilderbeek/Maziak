#ifndef MAZIAKINTGRID_H
#define MAZIAKINTGRID_H

#include <iosfwd>
#include <vector>

namespace ribi {
namespace maziak {

using IntGrid = std::vector<std::vector<int>>;

///Creates a binary maze, in which 0 denotes a road, and 1 a wall
IntGrid CreateIntGrid(
  const int n_cols,
  const int n_rows,
  const int rng_seed
);

int get_n_cols(const IntGrid& g) noexcept;
int get_n_rows(const IntGrid& g) noexcept;

///Determine if the size if good to make a maze from.
///Minimum size is 7, because this is the lowest size
///in which there is the minimum number of dead ends
///to host an exit, sword, prisoner
constexpr bool IsValidSize(const int sz) noexcept
{
  return sz >= 7 && sz % 4 == 3;
}

std::ostream& operator<<(std::ostream& os, const IntGrid& v) noexcept;

} //~namespace maziak
} //~namespace ribi


#endif // MAZIAKINTGRID_H
