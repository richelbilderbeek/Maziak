#ifndef MAZIAKSOLUTIONMAZE_H
#define MAZIAKSOLUTIONMAZE_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>

#include "maziakintmaze.h"
#include "maziakfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace maziak {

///SolutionMaze displays the solution from a goal (as obtained
///from a DistanceMaze) and a current position
/*

* : solution
. : other corridors

 ***...
 *
 ***.. .
 . . . .
 . .....

*/

class SolutionMaze
{
public:
  SolutionMaze();
  SolutionMaze(
    const DistancesMaze& maze,
    const int x,
    const int y
  );

  int Get(const int x, const int y) const noexcept;

  const auto& Get() const noexcept { return m_maze; }

private:
  IntMaze m_maze;
};

IntMaze CreateSolution(
  const DistancesMaze& maze,
  const int x,
  const int y
);

int GetSize(const SolutionMaze& m) noexcept;

bool IsSquare(const SolutionMaze& m);

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKSOLUTIONMAZE_H
