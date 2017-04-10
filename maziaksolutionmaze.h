#ifndef MAZIAKSOLUTIONMAZE_H
#define MAZIAKSOLUTIONMAZE_H

#include <iosfwd>
#include <vector>

#include "maziakintmaze.h"
#include "maziakfwd.h"

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

  bool CanGet(const Coordinat c) const noexcept;
  int Get(const Coordinat c) const noexcept;

  const auto& Get() const noexcept { return m_maze; }

private:
  IntMaze m_maze;
};

IntMaze CreateSolution(
  const DistancesMaze& maze,
  const Coordinat& source
);

int get_n_cols(const SolutionMaze& m);
int get_n_rows(const SolutionMaze& m) noexcept;

bool IsSquare(const SolutionMaze& m);

std::ostream& operator<<(std::ostream& os, const SolutionMaze& m) noexcept;

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKSOLUTIONMAZE_H
