#ifndef MAZIAKSOLUTIONMAZE_H
#define MAZIAKSOLUTIONMAZE_H

#include <iosfwd>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
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
    const Coordinat c
  );

  int Get(const int x, const int y) const noexcept;

  const auto& Get() const noexcept { return m_maze; }

private:
  IntMaze m_maze;
};

IntMaze CreateSolution(
  const DistancesMaze& maze,
  const Coordinat& source
);

int get_n_rows(const SolutionMaze& m) noexcept;

bool IsSquare(const SolutionMaze& m);

std::ostream& operator<<(std::ostream& os, const SolutionMaze& m) noexcept;

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKSOLUTIONMAZE_H
