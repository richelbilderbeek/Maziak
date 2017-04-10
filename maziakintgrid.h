#ifndef MAZIAKINTGRID_H
#define MAZIAKINTGRID_H

#include <iosfwd>
#include <vector>

namespace ribi {
namespace maziak {

using IntGrid = std::vector<std::vector<int>>;

//Creates a binary maze
// 0 : path
// 1 : wall
IntGrid CreateIntGrid(
  const int n_cols,
  const int n_rows,
  const int rng_seed
);

///Classic implementation
IntGrid CreateIntGridImpl1(
  const int n_cols,
  const int n_rows,
  const int rng_seed
);

///Newer implementation
IntGrid CreateIntGridImpl2(
  const int n_cols,
  const int n_rows,
  const int rng_seed
);

int get_n_cols(const IntGrid& g) noexcept;
int get_n_rows(const IntGrid& g) noexcept;

///Determine if the size if good to make a maze from
constexpr bool IsValidSize(const int sz) noexcept
{
  return sz >= 7 && sz % 4 == 3;
}

std::ostream& operator<<(std::ostream& os, const IntGrid& v) noexcept;

} //~namespace maziak
} //~namespace ribi


#endif // MAZIAKINTGRID_H
