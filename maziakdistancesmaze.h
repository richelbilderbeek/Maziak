#ifndef MAZIAKDISTANCESMAZE_H
#define MAZIAKDISTANCESMAZE_H

#include <vector>

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
    const int goal_x,
    const int goal_y
  );

  bool CanGet(const int x, const int y) const noexcept;
  const auto& Get() const noexcept { return m_distances; }
  int Get(const int x, const int y) const noexcept;

  //TODO: make obsolete
  int GetSize() const noexcept;

private:
  std::vector<std::vector<int>> m_distances;

};

std::vector<std::vector<int>> CalculateDistances(
  const IntMaze& maze,
  const int x,
  const int y
) noexcept;

int GetSize(const DistancesMaze& m) noexcept;

std::ostream& operator<<(std::ostream& os, const DistancesMaze& m) noexcept;

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKDISTANCESMAZE_H
