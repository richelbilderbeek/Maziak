#include "maziakintmaze.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <gsl/gsl_assert>
#include "maziakcoordinat.h"
#include "maziakdistancesmaze.h"
#include "maziakhelper.h"

ribi::maziak::IntMaze::IntMaze()
  : m_int_grid{}
{

}

ribi::maziak::IntMaze::IntMaze(
  const int n_cols,
  const int n_rows,
  const int rng_seed
) : m_int_grid{CreateIntGrid(n_cols, n_rows, rng_seed)}
{
  Expects(IsValidSize(n_cols));
  Expects(IsValidSize(n_rows));
}

ribi::maziak::IntMaze::IntMaze(
  const IntGrid& int_grid
)
  : m_int_grid{int_grid}
{
  //m_dead_ends = CollectDeadEnds(m_int_grid);
}

bool ribi::maziak::IntMaze::CanGet(const Coordinat c) const noexcept
{
  const auto x = get_x(c);
  const auto y = get_y(c);
  return x >= 0 && x < get_n_cols(*this)
      && y >= 0 && y < get_n_rows(*this);
}

std::vector<ribi::maziak::Coordinat> ribi::maziak::CollectDeadEnds(
  const IntMaze& m) noexcept
{
  return CollectDeadEnds(m.Get());
}

std::vector<ribi::maziak::Coordinat> ribi::maziak::CollectDeadEnds(
  const std::vector<std::vector<int>>& grid) noexcept
{
  const auto n_rows = get_n_rows(grid);
  const auto n_cols = get_n_cols(grid);

  std::vector<Coordinat> dead_ends;

  for (int y=1; y!=n_rows-1; ++y)
  {
    for (int x=1; x!=n_cols-1; ++x)
    {
      if (grid[y][x] != 0) continue; //Continue if here is a wall
      const auto adjacent = get_adjacent_4(Coordinat(x, y));
      const auto n =
        std::count_if(std::begin(adjacent), std::end(adjacent),
        [grid](const Coordinat c)
        {
          assert(get_y(c) >= 0);
          assert(get_x(c) >= 0);
          assert(!grid.empty());
          assert(get_y(c) < static_cast<int>(grid.size()));
          assert(get_x(c) < static_cast<int>(grid[0].size()));
          return grid[get_y(c)][get_x(c)] == 1;
        }
      );

      if (n == 3) dead_ends.push_back(Coordinat(x,y));

    }
  }
  return dead_ends;
}


int ribi::maziak::Count(const int i, const IntMaze& m)
{
  return Count(i, m.Get());
}

ribi::maziak::IntMaze ribi::maziak::CreateIntMaze(
  const int n_cols,
  const int n_rows,
  const int seed
)
{
  Expects(IsValidSize(n_cols));
  Expects(IsValidSize(n_rows));
  return IntMaze{n_cols, n_rows, seed};
}

int ribi::maziak::IntMaze::Get(const Coordinat c) const noexcept
{
  assert(CanGet(c));
  const auto x = get_x(c);
  const auto y = get_y(c);
  return m_int_grid[y][x];
}

ribi::maziak::DistancesMaze ribi::maziak::CreateDistancesMaze(
  const IntMaze& m,
  const Coordinat target
  )
{
  return DistancesMaze{m,target};
}

int ribi::maziak::get_n_cols(const IntMaze& m) noexcept
{
  assert(get_n_rows(m));
  return static_cast<int>(m.Get()[0].size());
}

int ribi::maziak::get_n_rows(const IntMaze& m) noexcept
{
  return static_cast<int>(m.Get().size());
}

bool ribi::maziak::operator==(const IntMaze& lhs, const IntMaze& rhs) noexcept
{
  return lhs.Get() == rhs.Get();
}

std::ostream& ribi::maziak::operator<<(
  std::ostream& os, const IntMaze& m) noexcept
{

  os << m.m_int_grid;
  /*
  std::transform(
    std::begin(m.m_dead_ends),
    std::end(m.m_dead_ends),
    std::ostream_iterator<std::string>(os, "\n"),
    [](const auto& p)
    {
      return '(' + std::to_string(p.first) + ',' + std::to_string(p.second) + ')';
    }
  );
  */
  return os;
}


