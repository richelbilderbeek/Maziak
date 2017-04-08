#ifndef MAZIAKMAZE_H
#define MAZIAKMAZE_H

#include <iosfwd>
#include <vector>

#include <random>
#include "maziakfwd.h"
#include "maziakmazesquare.h"
#include "maziakintmaze.h"

namespace ribi {
namespace maziak {

struct Maze
{
  Maze(
    const int n_cols,
    const int n_rows,
    const int rng_seed
  );

  ///Animate the enemies and prisoners in sight
  ///(all others are just standing still)
  ///Need RNG engine for movement of the enemies
  void AnimateEnemiesAndPrisoners(
    const int x,
    const int y,
    const int view_width,
    const int view_height,
    std::mt19937& rng_engine
    ) noexcept;

  ///Can I get a value at (x,y)?
  bool CanGet(const int x, const int y) const noexcept;

  ///Can I set a value at (x,y)?
  bool CanSet(const int x, const int y) const noexcept;

  ///Can a player move to coordinat (x,y) ?
  bool CanMoveTo(
    const int x, const int y,
    const bool hasSword,
    const bool showSolution
  ) const noexcept;

  MazeSquare Get(const int x, const int y) const;
  const auto& Get() const noexcept { return m_maze; }

  void Set(const int x, const int y, const MazeSquare s);

  private:

  ///Locations of walls, swords, prisoners, enemies
  std::vector<std::vector<MazeSquare>> m_maze;

  friend std::ostream& operator<<(std::ostream& os, const Maze& m) noexcept;
};

int Count(const MazeSquare i, const Maze& m);

///Create a maze with prisoners, swords, exit, begin and enemies
std::vector<std::vector<MazeSquare>> CreatePopulatedMaze(
  const IntMaze& int_maze,
  std::mt19937& rng_engine
);

///Create a maze with prisoners, swords, exit, begin and enemies
std::vector<std::vector<MazeSquare>> CreatePopulatedMaze(
  const IntMaze& int_maze,
  const int rng_seed
);

///Collect all dead ends
std::vector<std::pair<int,int>> CollectDeadEnds(const Maze& maze) noexcept;

/// Minimal complete maze
/*

  XXXXXXXXXXXXXXX
  X  +X+    X+  X
  X XXXXX XXXXX X
  X    ZX X  +X X
  XXX XXX X XXX X
  X:X X.X   XZ  X
  X X X X XXXXX X
  X             X
  XXXXX X X XXX X
  X     X X  ZX X
  X XXX X X XXXXX
  X   X X!X   X X
  XXX X XXXXX X X
  X   X     X   X
  XXXXXXXXXXXXXXX

*/
Maze CreateTestMaze1() noexcept;


///Convert walls and roads, zeroes and ones to MazeSquares
std::vector<std::vector<MazeSquare>> ConvertMaze(
  const IntMaze& int_maze
) noexcept;

DistancesMaze CreateDistancesMaze(
  const Maze& m,
  const std::pair<int, int>& target
);

std::pair<int,int> FindExit(const Maze& m);
std::pair<int,int> FindStart(const Maze& m);

int get_n_cols(const Maze& m) noexcept;
int get_n_rows(const Maze& m) noexcept;

std::string to_str(const Maze& m) noexcept;
std::string to_str(const std::vector<std::vector<MazeSquare>>& m) noexcept;

bool operator==(const Maze& lhs, const Maze& rhs) noexcept;

std::ostream& operator<<(std::ostream& os, const Maze& m) noexcept;
std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<MazeSquare>>& m) noexcept;
std::ostream& operator<<(std::ostream& os, const std::vector<MazeSquare>& m) noexcept;

} //~namespace maziak
} //~namespace ribi


#endif // MAZIAKMAZE_H
