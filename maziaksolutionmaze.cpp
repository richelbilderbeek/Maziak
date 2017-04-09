#include "maziaksolutionmaze.h"

#include <cassert>
#include <iostream>

#include "maziakdistancesmaze.h"
#include "maziakintmaze.h"

ribi::maziak::SolutionMaze::SolutionMaze()
  : m_maze{}
{

}

ribi::maziak::SolutionMaze::SolutionMaze(
  const DistancesMaze& maze,
  const Coordinat c
) : m_maze(CreateSolution(maze,c))
{
  assert(get_n_cols(maze) == get_n_cols(m_maze));
  assert(get_n_rows(maze) == get_n_rows(m_maze));
}

bool ribi::maziak::SolutionMaze::CanGet(const Coordinat c) const noexcept
{
  return m_maze.CanGet(c);
}

ribi::maziak::IntMaze ribi::maziak::CreateSolution(
  const DistancesMaze& distances,
  const Coordinat& source
)
{
  const auto n_cols = get_n_cols(distances);
  const auto n_rows = get_n_rows(distances);
  const auto maxx = n_cols - 1;
  const auto maxy = n_rows - 1;
  auto x = get_x(source);
  auto y = get_y(source);

  std::vector<std::vector<int>> solution(n_rows, std::vector<int>(n_cols,0));
  {
    int distance = distances.Get(Coordinat(x, y)) - 1;
    while (distance >= 0)
    {
      //We must be where we are now
      assert(y >= 0);
      assert(x >= 0);
      assert(!solution.empty());
      assert(y < static_cast<int>(solution.size()));
      assert(x < static_cast<int>(solution[0].size()));
      solution[y][x] = 1;
      if (x > 0    && distances.Get(Coordinat(x-1,y)) == distance ) { --x; --distance; continue; }
      if (x < maxx && distances.Get(Coordinat(x+1,y)) == distance ) { ++x; --distance; continue; }
      if (y > 0    && distances.Get(Coordinat(x,y-1)) == distance ) { --y; --distance; continue; }
      if (y < maxy && distances.Get(Coordinat(x,y+1)) == distance ) { ++y; --distance; continue; }
    }
  }
  const IntMaze maze(solution);
  return maze;
}

int ribi::maziak::SolutionMaze::Get(const Coordinat c) const noexcept
{
  assert(CanGet(c));
  return m_maze.Get(c);
}

int ribi::maziak::get_n_cols(const SolutionMaze& m)
{
  assert(get_n_rows(m));
  return get_n_cols(m.Get());
}

int ribi::maziak::get_n_rows(const SolutionMaze& m) noexcept
{
  return get_n_rows(m.Get());
}

std::ostream& ribi::maziak::operator<<(
  std::ostream& os, const SolutionMaze& m) noexcept
{
  os << m.Get();
  return os;
}
