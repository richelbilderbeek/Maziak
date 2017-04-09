#ifndef MAZIAKDISTANCESMAZE_H
#define MAZIAKDISTANCESMAZE_H

#include <vector>

#include "maziakcoordinat.h"
#include "maziakfwd.h"
#include "maziakmazesquare.h"

namespace ribi {
namespace maziak {

///DistancesMaze displays the distances from a goal
/*

 456789
 3
 21012 8
   1 3 7
 4323456

*/

class DistancesMaze
{
public:
  DistancesMaze();

  DistancesMaze(
    const IntMaze& maze,
    const Coordinat target
  );

  DistancesMaze(
    const Maze& maze,
    const Coordinat goal
  );

  bool CanGet(const Coordinat c) const noexcept;
  const auto& Get() const noexcept { return m_distances; }
  int Get(const Coordinat c) const noexcept;

private:
  std::vector<std::vector<int>> m_distances;

};

std::vector<std::vector<int>> CalculateDistances(
  const IntMaze& maze,
  const Coordinat c
) noexcept;

std::vector<std::vector<int>> CalculateDistances(
  const Maze& maze,
  const Coordinat c
) noexcept;

int get_n_cols(const DistancesMaze& m) noexcept;
int get_n_rows(const DistancesMaze& m) noexcept;

std::ostream& operator<<(std::ostream& os, const DistancesMaze& m) noexcept;

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKDISTANCESMAZE_H
