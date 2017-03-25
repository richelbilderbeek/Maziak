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
IntGrid CreateIntGrid(const int sz, const int rng_seed);

int get_n_cols(const IntGrid& g) noexcept;
int get_n_rows(const IntGrid& g) noexcept;

///Determine if the size if good to make a maze from
bool IsValidSize(const int sz) noexcept;

std::ostream& operator<<(std::ostream& os, const IntGrid& v) noexcept;

} //~namespace maziak
} //~namespace ribi


#endif // MAZIAKINTGRID_H
