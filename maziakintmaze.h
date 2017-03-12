#ifndef MAZIAKINTMAZE_H
#define MAZIAKINTMAZE_H

#include <iosfwd>
#include <random>
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
  explicit IntMaze(const IntGrid& int_grid, const int rng_seed = 42);

  bool CanGet(const int x, const int y) const noexcept;

  int Get(const int x, const int y) const noexcept;

  const auto& Get() const noexcept { return m_int_grid; }

  ///Already shuffled, m_dead_ends[0] is the suggested initial coordinat for the player
  const auto& GetDeadEnds() const noexcept { return m_dead_ends; }

  ///Find the distances to (x,y) in walking squared
  DistancesMaze GetDistancesMaze(
    const int x,
    const int y
  ) const noexcept;

  private:

  std::vector<std::pair<int,int>> m_dead_ends;
  IntGrid m_int_grid;
  std::mt19937 m_rng_engine;

  ///From http://www.richelbilderbeek.nl/CppGetDeadEnds.htm
  std::vector<std::pair<int,int>> CollectDeadEnds(
    const IntGrid& maze) noexcept;


  friend std::ostream& operator<<(std::ostream& os, const IntMaze& m) noexcept;
};

IntMaze CreateIntMaze(const int size);

int GetSize(const IntMaze& m) noexcept;

bool IsSquare(const IntMaze& m);

std::ostream& operator<<(std::ostream& os, const IntMaze& m) noexcept;

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKINTMAZE_H
