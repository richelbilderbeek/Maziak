#include "maziaksolutionmaze.h"

#include <cassert>

#include "maziakdistancesmaze.h"
#include "maziakintmaze.h"



ribi::maziak::SolutionMaze::SolutionMaze()
  : m_maze{}
{

}

ribi::maziak::SolutionMaze::SolutionMaze(
  const DistancesMaze& maze,
  const int x,
  const int y
) : m_maze(CreateSolution(maze,x,y))
{

}

//From http://www.richelbilderbeek.nl/GetDistancesPath.htm
ribi::maziak::IntMaze ribi::maziak::CreateSolution(
  const DistancesMaze& distances,
  const int player_x,
  const int player_y
)
{
  const int size = distances.GetSize();

  std::vector<std::vector<int> > solution(size, std::vector<int>(size,0));
  {
    int x = player_x;
    int y = player_y;
    int distance = distances.Get(x,y) - 1;
    while (distance >= 0)
    {
      //We must be where we are now
      solution[y][x] = 1;
      if ( x!=0      && distances.Get(x-1,y) == distance ) { --x; --distance; continue; }
      if ( x!=size-1 && distances.Get(x+1,y) == distance ) { ++x; --distance; continue; }
      if ( y!=0      && distances.Get(x,y-1) == distance ) { --y; --distance; continue; }
      if ( y!=size-1 && distances.Get(x,y+1) == distance ) { ++y; --distance; continue; }
    }
  }

  const IntMaze maze(solution);
  return maze;
}

int ribi::maziak::SolutionMaze::Get(const int x, const int y) const noexcept
{
  return m_maze.Get(x,y);
}

int ribi::maziak::SolutionMaze::GetSize() const noexcept
{
  return m_maze.GetSize();
}

bool ribi::maziak::IsSquare(const SolutionMaze& m)
{
  return IsSquare(m.Get());
}
