#ifndef MAZIAKINTGRID_H
#define MAZIAKINTGRID_H

#include <vector>

namespace ribi {
namespace maziak {

using IntGrid = std::vector<std::vector<int>>;

//Creates a maze
// 0 : path
// 1 : wall
///From http://www.richelbilderbeek.nl/CppCreateMaze.htm
IntGrid CreateIntGrid(const int sz);

int GetSize(const IntGrid& g) noexcept;

///Determine if the size if good to make a maze from
bool IsValidSize(const int sz) noexcept;

} //~namespace maziak
} //~namespace ribi


#endif // MAZIAKINTGRID_H
