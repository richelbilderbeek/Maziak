#include "maziakmaze.h"

#include <cassert>
#include <iostream>
#include <iterator>
#include <sstream>
#include <gsl/gsl_assert>

#include "maziakhelper.h"
#include "maziakintmaze.h"

ribi::maziak::Maze::Maze(
  const int n_cols,
  const int n_rows,
  const int rng_seed
) : m_maze{CreatePopulatedMaze(CreateIntMaze(n_cols, n_rows, rng_seed), rng_seed)}
{
  Ensures(FindExit(*this).first  >= 0);
  Ensures(FindStart(*this).first >= 0);
}

void ribi::maziak::Maze::MakeEnemiesMove(
  const int x,
  const int y,
  const int view_width,
  const int view_height,
  std::mt19937& rng_engine
  ) noexcept
{
  //Move them
  const int minx = std::max(0,x - view_width );
  const int miny = std::max(0,y - view_height);
  const int maxy = std::min(get_n_rows(*this),y + view_height);
  const int maxx = std::min(get_n_rows(*this),x + view_width);
  assert(miny >= 0);
  assert(miny <= get_n_rows(*this));
  assert(maxy >= 0);
  assert(maxy <= get_n_rows(*this));
  assert(minx >= 0);
  assert(minx <= get_n_rows(*this));
  assert(maxx >= 0);
  assert(maxx <= get_n_rows(*this));
  assert(miny <= maxy);
  assert(minx <= maxx);
  for (int row=miny; row!=maxy; ++row)
  {
    assert(row >= 0);
    assert(row < get_n_rows(*this));
    for (int col=minx; col!=maxx; ++col)
    {
      //msEnemy1 changes to msEnemy2
      //Only msEnemy2 moves, after moving turning to msEnemy1
      assert(col >= 0);
      assert(col < get_n_rows(*this));
      const MazeSquare s = Get(Coordinat(col,row));

      if (s == MazeSquare::enemy)
      {
        //msEnemy 2 tries to walk and becomes msEnemy1
        std::vector<Coordinat > moves;
        if (row > y && row >        1 && Get(Coordinat(col,row-1)) == MazeSquare::empty) moves.push_back(std::make_pair(col,row-1));
        if (col < x && col < maxx - 1 && Get(Coordinat(col+1,row)) == MazeSquare::empty) moves.push_back(std::make_pair(col+1,row));
        if (row < y && row < maxy - 1 && Get(Coordinat(col,row+1)) == MazeSquare::empty) moves.push_back(std::make_pair(col,row+1));
        if (col > x && col >        1 && Get(Coordinat(col-1,row)) == MazeSquare::empty) moves.push_back(std::make_pair(col-1,row));
        //Pick a random move
        if (!moves.empty())
        {
          std::shuffle(std::begin(moves),std::end(moves), rng_engine);
          Set(moves[0], MazeSquare::enemy);
          Set(Coordinat(col,row), MazeSquare::empty);
        }
      }
    }
  }
}

bool ribi::maziak::Maze::CanGet(const Coordinat c) const noexcept
{
  const auto x = get_x(c);
  const auto y = get_y(c);
  return x >= 0 && x < get_n_cols(*this)
    && y >= 0 && y < get_n_rows(*this);
}

bool ribi::maziak::Maze::CanMoveTo(
  const Coordinat c,
  const bool has_sword,
  const bool show_solution) const noexcept
{
  const auto x = get_x(c);
  const auto y = get_y(c);

  //Bump into edge
  if (x < 0) return false;
  if (y < 0) return false;
  if (y >= get_n_rows(*this)) return false;
  if (x >= get_n_cols(*this)) return false;
  const auto& s = m_maze[y][x];
  //Bump into wall
  if (s == MazeSquare::wall) return false;
  //Bump into sword
  if (s == MazeSquare::sword && has_sword) return false;
  //Bump into prisoner
  if (show_solution && s == MazeSquare::prisoner) return false;
  //Bump into empty/enemy/exit, so player can move there
  return true;
}



std::vector<std::vector<ribi::maziak::MazeSquare>> ribi::maziak::ConvertMaze(
  const IntMaze& int_maze
) noexcept
{
  std::vector<std::vector<MazeSquare>> m;
  m.reserve(int_maze.Get().size());
  std::transform(
    std::begin(int_maze.Get()),
    std::end(int_maze.Get()),
    std::back_inserter(m),
    [](const std::vector<int>& row)
    {
      std::vector<MazeSquare> s;
      s.reserve(row.size());
      std::transform(
        std::begin(row),
        std::end(row),
        std::back_inserter(s),
        [](const int i) { return static_cast<MazeSquare>(i); }
      );
      return s;
    }
  );
  //const int sz = GetSize(int_maze);
  //return ConvertMatrix<int,MazeSquare>(int_maze.Get());
  return m;
}

int ribi::maziak::Count(const MazeSquare i, const Maze& m)
{
  return Count(i, m.Get());
}

std::vector<std::vector<ribi::maziak::MazeSquare>> ribi::maziak::CreatePopulatedMaze(
  const IntMaze& int_maze,
  const int rng_seed
)
{
  assert(rng_seed >= 0);
  std::mt19937 rng_engine{static_cast<long unsigned int>(rng_seed)};
  return CreatePopulatedMaze(int_maze, rng_engine);
}
std::vector<std::vector<ribi::maziak::MazeSquare>> ribi::maziak::CreatePopulatedMaze(
  const IntMaze& int_maze,
  std::mt19937& rng_engine)
{
  const int sz = get_n_rows(int_maze);
  std::vector<std::vector<MazeSquare>> maze {
    ConvertMaze(int_maze)
  };


  std::vector<Coordinat> dead_ends = CollectDeadEnds(int_maze);
  std::shuffle(std::begin(dead_ends), std::end(dead_ends), rng_engine);
  const int nDeadEnds = dead_ends.size();
  std::uniform_int_distribution<int> distribution(0,nDeadEnds-1); //Inclusive max
  assert(nDeadEnds >= 2);
  const int nSwords    = (nDeadEnds - 2) / 3;
  const int nPrisoners = (nDeadEnds - 2) / 10;
  const int nEnemies   = (nDeadEnds - 2) / 4;
  {
    //Set a minimum distance for the player to travel
    //while (1)
    for (int i=0; ;++i)
    {
      const double x1 = static_cast<double>(dead_ends[0].first );
      const double y1 = static_cast<double>(dead_ends[0].second);
      const double x2 = static_cast<double>(dead_ends[1].first );
      const double y2 = static_cast<double>(dead_ends[1].second);
      const double a = x1 - x2;
      const double b = y1 - y2;
      // Use 0.65, as 0.75 could not always be solved
      const double minDist = 0.40 * static_cast<double>(sz);
      if (std::sqrt( (a * a) + (b * b) ) > minDist)
      {
        break;
      }
      else
      {
        const int de_a{distribution(rng_engine)};
        const int de_b{distribution(rng_engine)};
        assert(de_a < static_cast<int>(dead_ends.size()));
        assert(de_b < static_cast<int>(dead_ends.size()));
        std::swap(dead_ends[0],dead_ends[de_a]);
        std::swap(dead_ends[1],dead_ends[de_b]);
      }
    }
  }
  //Set start
  {
    const int x = dead_ends[0].first;
    const int y = dead_ends[0].second;
    assert(maze[y][x] == MazeSquare::empty);
    maze[y][x] = MazeSquare::start;
  }
  //Set exit
  {
    const int x = dead_ends[1].first;
    const int y = dead_ends[1].second;
    assert(maze[y][x] == MazeSquare::empty);
    maze[y][x] = MazeSquare::exit;
  }


  std::vector<Coordinat >::const_iterator deadEndIterator = dead_ends.begin() + 2;

  {
    //Place swords in maze, only in dead ends
    for (int i=0; i!=nSwords; ++i)
    {
      assert(deadEndIterator != dead_ends.end());
      const int x = (*deadEndIterator).first;
      const int y = (*deadEndIterator).second;
      assert(maze[y][x] == MazeSquare::empty);
      maze[y][x] = MazeSquare::sword;
      ++deadEndIterator;
    }
    //Place prisoners in maze, only in dead ends
    for (int i=0; i!=nPrisoners; ++i)
    {
      assert(deadEndIterator != dead_ends.end());
      const int x = (*deadEndIterator).first;
      const int y = (*deadEndIterator).second;
      assert(maze[y][x] == MazeSquare::empty);
      maze[y][x] = MazeSquare::prisoner;
      ++deadEndIterator;
    }

    for (int i=0; i!=nEnemies; ++i)
    {
      assert(deadEndIterator != dead_ends.end());
      const int x = (*deadEndIterator).first;
      const int y = (*deadEndIterator).second;
      assert(maze[y][x] == MazeSquare::empty);
      maze[y][x] = MazeSquare::enemy;
      ++deadEndIterator;
    }
  }
  return maze;
}

std::vector<ribi::maziak::Coordinat> ribi::maziak::CollectDeadEnds(
  const Maze& m) noexcept
{
  const auto n_cols = get_n_cols(m);
  const auto n_rows = get_n_rows(m);

  std::vector<Coordinat> dead_ends;

  for (int y=1; y!=n_rows-1; ++y)
  {
    for (int x=1; x!=n_cols-1; ++x)
    {
      const Coordinat here{x,y};
      if (m.Get(here) == MazeSquare::wall) continue;
      //if (m[y][x] != 0) continue; //Continue if here is a wall
      const auto adjacent = get_adjacent_4(here);
      const auto n = std::count_if(
        std::begin(adjacent), std::end(adjacent),
        [m](const Coordinat c)
        {
          return m.Get(c) == MazeSquare::wall;
        }
      );
      assert(n != 4);
      if (n == 3) dead_ends.push_back( { x,y } );

    }
  }
  return dead_ends;
}

ribi::maziak::Maze ribi::maziak::CreateTestMaze1() noexcept
{
  const int n_cols{19};
  const int n_rows{15};
  const int rng_seed{12};
  static_assert(IsValidSize(n_cols), "");
  static_assert(IsValidSize(n_rows), "");
  return Maze{n_cols, n_rows, rng_seed};
}

ribi::maziak::Coordinat ribi::maziak::FindExit(const Maze& m)
{
  return FindFirst(m, MazeSquare::exit);
}

///Find a first maze square of the desired type
ribi::maziak::Coordinat ribi::maziak::FindFirst(const Maze& m, const MazeSquare s)
{
  const int n_cols{get_n_cols(m)};
  const int n_rows{get_n_rows(m)};
  if (s == MazeSquare::wall)
  {
    assert(m.Get(Coordinat(2, 2)) == MazeSquare::wall);
    return {2, 2};
  }
  for (int row{1}; row<n_rows; row+=2)
  {
    for (int col{1}; col<n_cols; col+=2)
    {
      if (m.Get(Coordinat(col,row)) == s) return { col, row};
    }
  }
  throw std::invalid_argument("Could not find first maze square");
}

ribi::maziak::Coordinat ribi::maziak::FindStart(const Maze& m)
{
  return FindFirst(m, MazeSquare::start);
}

ribi::maziak::MazeSquare ribi::maziak::Maze::Get(
  const Coordinat c) const
{
  Expects(CanGet(c));
  const auto x = get_x(c);
  const auto y = get_y(c);
  return m_maze[y][x];
}

int ribi::maziak::get_n_cols(const Maze& m) noexcept
{
  assert(get_n_rows(m));
  return static_cast<int>(m.Get()[0].size());
}

int ribi::maziak::get_n_rows(const Maze& m) noexcept
{
  return static_cast<int>(m.Get().size());
}

void ribi::maziak::Maze::Set(const Coordinat c, const MazeSquare s)
{
  Expects(CanSet(c));
  const auto x = get_x(c);
  const auto y = get_y(c);
  m_maze[y][x] = s;
  Ensures(Get(c) == s);
}

std::ostream& ribi::maziak::operator<<(
  std::ostream& os, const Maze& m) noexcept
{
  os << "Maze:\n" << m.m_maze;
  return os;
}

std::string ribi::maziak::to_str(const Maze& m) noexcept
{
  std::stringstream s;
  s << m;
  return s.str();
}

std::string ribi::maziak::to_str(const std::vector<std::vector<MazeSquare>>& m) noexcept
{
  std::stringstream s;
  s << m;
  return s.str();
}

bool ribi::maziak::operator==(const Maze& lhs, const Maze& rhs) noexcept
{
  return lhs.Get() == rhs.Get();
}

std::ostream& ribi::maziak::operator<<(std::ostream& os, const std::vector<std::vector<MazeSquare>>& m) noexcept
{
  std::copy(
    std::begin(m),
    std::end(m),
    std::ostream_iterator<std::vector<MazeSquare>>(os, "\n")
  );
  return os;
}
std::ostream& ribi::maziak::operator<<(std::ostream& os, const std::vector<MazeSquare>& row) noexcept
{
  os << std::accumulate(
    std::begin(row),
    std::end(row),
    std::string(),
    [](std::string init, const MazeSquare s)
    {
      return init + to_char(s);
    }
  );
  return os;
}
