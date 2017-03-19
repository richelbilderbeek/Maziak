#ifndef MAZIAKINTMAZE_H
#define MAZIAKINTMAZE_H

#include <iosfwd>
#include <vector>

#include "maziakfwd.h"
#include "maziakintgrid.h"

namespace ribi {
namespace maziak {

///A maze using integers
/// 0 : path
/// 1 : wall
struct IntMaze
{
  explicit IntMaze();
  explicit IntMaze(const int sz, const int rng_seed = 42);
  explicit IntMaze(const IntGrid& int_grid);

  ///Can I access this coordinat?
  bool CanGet(const int x, const int y) const noexcept;

  ///Read the coordinat
  int Get(const int x, const int y) const noexcept;

  ///Read the raw grid
  const auto& Get() const noexcept { return m_int_grid; }

  private:
  IntGrid m_int_grid;
  friend std::ostream& operator<<(std::ostream& os, const IntMaze& m) noexcept;
};

///Collect all dead ends
std::vector<std::pair<int,int>> CollectDeadEnds(const IntGrid& grid) noexcept;

///Collect all dead ends
std::vector<std::pair<int,int>> CollectDeadEnds(const IntMaze& maze) noexcept;

///Count the occurance of i in the IntMaze
int Count(const int i, const IntMaze& m);

///Find the distances to (x,y) in walking squared
DistancesMaze CreateDistancesMaze(
  const IntMaze& m,
  const int x,
  const int y
);

DistancesMaze CreateDistancesMaze(
  const IntMaze& m,
  const std::pair<int, int>& target
);

IntMaze CreateIntMaze(const int size, const int seed);

int GetSize(const IntMaze& m) noexcept;

bool IsSquare(const IntMaze& m);

bool operator==(const IntMaze& lhs, const IntMaze& rhs) noexcept;

std::ostream& operator<<(std::ostream& os, const IntMaze& m) noexcept;

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKINTMAZE_H
