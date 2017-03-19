#include "maziakintmaze.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <gsl/gsl_assert>
#include "maziakdistancesmaze.h"
#include "maziakhelper.h"

ribi::maziak::IntMaze::IntMaze()
  : m_dead_ends{}, m_int_grid{}, m_rng_engine(0)
{

}

ribi::maziak::IntMaze::IntMaze(const int sz, const int rng_seed)
  : m_dead_ends{}, m_int_grid{}, m_rng_engine(rng_seed)
{
  Expects(IsValidSize(sz));
  m_int_grid = CreateIntGrid(sz);
  m_dead_ends = CollectDeadEnds(m_int_grid);
}

ribi::maziak::IntMaze::IntMaze(
  const IntGrid& int_grid,
  const int rng_seed
)
  : m_dead_ends{}, m_int_grid{int_grid}, m_rng_engine(rng_seed)
{
  m_dead_ends = CollectDeadEnds(m_int_grid);
}

bool ribi::maziak::IntMaze::CanGet(const int x, const int y) const noexcept
{
  return x >= 0 && x < GetSize(*this)
      && y >= 0 && y < GetSize(*this);
}

std::vector<std::pair<int,int>> ribi::maziak::IntMaze::CollectDeadEnds(
  const std::vector<std::vector<int>>& maze) noexcept
{
  const int size = maze.size();

  std::vector<std::pair<int,int>> dead_ends;

  for (int y=1; y!=size-1; ++y)
  {
    for (int x=1; x!=size-1; ++x)
    {
      if (maze[y][x] != 0) continue; //Continue if here is a wall
      const int nWalls
        = (maze[y+1][x  ] == 1 ? 1 : 0)
        + (maze[y-1][x  ] == 1 ? 1 : 0)
        + (maze[y  ][x+1] == 1 ? 1 : 0)
        + (maze[y  ][x-1] == 1 ? 1 : 0);
      if (nWalls == 3) dead_ends.push_back(std::make_pair(x,y));

    }
  }

  //Shuffle them
  std::shuffle(dead_ends.begin(), dead_ends.end(),m_rng_engine);
  return dead_ends;
}

int ribi::maziak::Count(const int i, const IntMaze& m)
{
  return Count(i, m.Get());
}

ribi::maziak::IntMaze ribi::maziak::CreateIntMaze(const int size, const int seed)
{
  Expects(IsValidSize(size));
  return IntMaze{size, seed};
}

int ribi::maziak::IntMaze::Get(const int x, const int y) const noexcept
{
  assert(CanGet(x,y));
  return m_int_grid[y][x];
}

ribi::maziak::DistancesMaze ribi::maziak::IntMaze::GetDistancesMaze(
  const int x,
  const int y
  ) const noexcept
{
  DistancesMaze maze(*this,x,y);
  return maze;
}

int ribi::maziak::GetSize(const IntMaze& m) noexcept
{
  assert(IsSquare(m));
  return static_cast<int>(m.Get().size());
}

bool ribi::maziak::IsSquare(const IntMaze& m)
{
  return IsSquare(m.Get());
}

std::ostream& ribi::maziak::operator<<(
  std::ostream& os, const IntMaze& m) noexcept
{

  os << m.m_int_grid << '\n';

  std::transform(
    std::begin(m.m_dead_ends),
    std::end(m.m_dead_ends),
    std::ostream_iterator<std::string>(os, "\n"),
    [](const auto& p)
    {
      return '(' + std::to_string(p.first) + ',' + std::to_string(p.second) + ')';
    }
  );
  return os;
}


