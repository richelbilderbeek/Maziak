#ifndef MAZIAKINTMAZE_H
#define MAZIAKINTMAZE_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#include <random>
#include "maziakfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace maziak {

///A maze using integers
/// 0 : path
/// 1 : wall
struct IntMaze
{
  using IntGrid = std::vector<std::vector<int>>;

  explicit IntMaze();
  explicit IntMaze(const int sz, const int rng_seed = 42);
  explicit IntMaze(const IntGrid& int_grid, const int rng_seed = 42);

  bool CanGet(const int x, const int y) const noexcept;

  int Get(const int x, const int y) const noexcept;

  const auto& Get() const noexcept { return m_int_grid; }

  ///Already shuffled, m_dead_ends[0] is the suggested initial coordinat for the player
  std::vector<std::pair<int,int>> GetDeadEnds() const noexcept { return m_dead_ends; }

  ///Find the distances to (x,y) in walking squared
  DistancesMaze GetDistancesMaze(
    const int x,
    const int y
  ) const noexcept;

  private:

  std::vector<std::pair<int,int> > m_dead_ends;
  IntGrid m_int_grid;
  std::mt19937 m_rng_engine;

  ///From http://www.richelbilderbeek.nl/CppGetDeadEnds.htm
  std::vector<std::pair<int,int>> CreateDeadEnds(
    const IntGrid& maze) noexcept;

  //Creates a maze
  // 0 : path
  // 1 : wall
  ///From http://www.richelbilderbeek.nl/CppCreateMaze.htm
  IntGrid CreateIntGrid(const int sz) noexcept;
};

int GetSize(const IntMaze& m) noexcept;

bool IsSquare(const IntMaze& m);

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKINTMAZE_H
