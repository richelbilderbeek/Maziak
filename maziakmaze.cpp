#include "maziakmaze.h"

#include <cassert>
#include <iostream>
#include <iterator>
#include <sstream>
#include <gsl/gsl_assert>
#include "ribi_random.h"

#include "maziakhelper.h"
#include "maziakintmaze.h"

/*
template <class Source, class Target>
    const std::vector<std::vector<Target> > ConvertMatrix(
        const std::vector<std::vector<Source> >& v)
{
  const int maxy = static_cast<int>(v.size());
  assert(maxy>0);
  const int maxx = static_cast<int>(v[0].size());
  std::vector<std::vector<Target> > t(maxy,std::vector<Target>(maxx));
  for (int y=0; y!=maxy; ++y)
  {
    for (int x=0; x!=maxx; ++x)
    {
      t[y][x] = static_cast<Target>(v[y][x]);
    }
  }
  return t;
}
*/

ribi::maziak::Maze::Maze(
  const int size,
  const int rng_seed
) : m_int_maze{CreateIntMaze(size, rng_seed)},
    m_maze{},
    m_rng_engine(rng_seed)
{
  m_maze = CreatePopulatedMaze(m_int_maze, m_rng_engine);
  Ensures(IsSquare(m_maze));
  Ensures(FindExit().first  >= 0);
  Ensures(FindStart().first >= 0);
}

void ribi::maziak::Maze::AnimateEnemiesAndPrisoners(
  const int x,
  const int y,
  const int view_width,
  const int view_height
  ) noexcept
{
  //Move them
  const int minx = std::max(0,x - view_width );
  const int miny = std::max(0,y - view_height);
  assert(IsSquare(m_maze));
  const int maxy = std::min(GetSize(*this),y + view_height);
  const int maxx = std::min(GetSize(*this),x + view_width);
  assert(miny >= 0);
  assert(miny <= GetSize(*this));
  assert(maxy >= 0);
  assert(maxy <= GetSize(*this));
  assert(minx >= 0);
  assert(minx <= GetSize(*this));
  assert(maxx >= 0);
  assert(maxx <= GetSize(*this));
  assert(miny <= maxy);
  assert(minx <= maxx);
  for (int row=miny; row!=maxy; ++row)
  {
    assert(row >= 0);
    assert(row < GetSize(*this));
    for (int col=minx; col!=maxx; ++col)
    {
      //msEnemy1 changes to msEnemy2
      //Only msEnemy2 moves, after moving turning to msEnemy1
      assert(col >= 0);
      assert(col < GetSize(*this));
      const MazeSquare s = Get(col,row);

      if (s == MazeSquare::msEnemy1)
      {
        //msEnemy1 changes to msEnemy2
        Set(col,row,MazeSquare::msEnemy2);
        continue;
      }
      else if (s == MazeSquare::msEnemy2)
      {
        //msEnemy 2 tries to walk and becomes msEnemy1
        std::vector<std::pair<int,int> > moves;
        if (row > y && row >        1 && Get(col,row-1) == MazeSquare::msEmpty) moves.push_back(std::make_pair(col,row-1));
        if (col < x && col < maxx - 1 && Get(col+1,row) == MazeSquare::msEmpty) moves.push_back(std::make_pair(col+1,row));
        if (row < y && row < maxy - 1 && Get(col,row+1) == MazeSquare::msEmpty) moves.push_back(std::make_pair(col,row+1));
        if (col > x && col >        1 && Get(col-1,row) == MazeSquare::msEmpty) moves.push_back(std::make_pair(col-1,row));
        //Pick a random move
        if (!moves.empty())
        {
          std::shuffle(std::begin(moves),std::end(moves),m_rng_engine);
          Set(moves[0].first,moves[0].second,MazeSquare::msEnemy1);
          Set(col,row,MazeSquare::msEmpty);
        }
      }
      else if (s==MazeSquare::msPrisoner1)
      {
        //Animate prisoners
        Set(col,row,MazeSquare::msPrisoner2);
      }
      else if (s==MazeSquare::msPrisoner2)
      {
        //Animate prisoners
        Set(col,row,MazeSquare::msPrisoner1);
      }
    }
  }
}

bool ribi::maziak::Maze::CanGet(const int x, const int y) const noexcept
{
  return x >= 0 && x < GetSize(*this)
    && y >= 0 && y < GetSize(*this);
}

bool ribi::maziak::Maze::CanMoveTo(
  const int x, const int y,
  const bool hasSword,
  const bool showSolution) const noexcept
{
  //Bump into edge
  if (x < 0) return false;
  if (y < 0) return false;
  const int maxy = static_cast<int>(m_maze.size());
  if (y >= maxy) return false;
  if (x >= static_cast<int>(m_maze[y].size())) return false;
  const MazeSquare s = m_maze[y][x];
  //Bump into wall
  if (s == MazeSquare::msWall) return false;
  //Bump into sword
  if (s == MazeSquare::msSword && hasSword) return false;
  //Bump into prisoner
  if (showSolution
    && (s == MazeSquare::msPrisoner1
     || s == MazeSquare::msPrisoner2) ) return false;
  //Bump into empty/enemy/exit, so player can move there
  return true;
}

bool ribi::maziak::Maze::CanSet(const int x, const int y) const noexcept
{
  return CanGet(x,y);
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
  std::mt19937& rng_engine)
{
  const int sz = GetSize(int_maze);
  std::vector<std::vector<MazeSquare>> maze {
    ConvertMaze(int_maze)
  };

  std::vector<std::pair<int,int>> dead_ends = int_maze.GetDeadEnds();
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
    assert(maze[y][x] == MazeSquare::msEmpty);
    maze[y][x] = MazeSquare::msStart;
  }
  //Set exit
  {
    const int x = dead_ends[1].first;
    const int y = dead_ends[1].second;
    assert(maze[y][x] == MazeSquare::msEmpty);
    maze[y][x] = MazeSquare::msExit;
  }


  std::vector<std::pair<int,int> >::const_iterator deadEndIterator = dead_ends.begin() + 2;

  {
    //Place swords in maze, only in dead ends
    for (int i=0; i!=nSwords; ++i)
    {
      assert(deadEndIterator != dead_ends.end());
      const int x = (*deadEndIterator).first;
      const int y = (*deadEndIterator).second;
      assert(maze[y][x] == MazeSquare::msEmpty);
      maze[y][x] = MazeSquare::msSword;
      ++deadEndIterator;
    }
    //Place prisoners in maze, only in dead ends
    for (int i=0; i!=nPrisoners; ++i)
    {
      assert(deadEndIterator != dead_ends.end());
      const int x = (*deadEndIterator).first;
      const int y = (*deadEndIterator).second;
      assert(maze[y][x] == MazeSquare::msEmpty);
      maze[y][x] = MazeSquare::msPrisoner1;
      ++deadEndIterator;
    }

    for (int i=0; i!=nEnemies; ++i)
    {
      assert(deadEndIterator != dead_ends.end());
      const int x = (*deadEndIterator).first;
      const int y = (*deadEndIterator).second;
      assert(maze[y][x] == MazeSquare::msEmpty);
      maze[y][x] = MazeSquare::msEnemy1;
      ++deadEndIterator;
    }
  }
  return maze;
}

std::pair<int,int> ribi::maziak::Maze::FindExit() const noexcept
{
  for (std::pair<int,int> p: GetIntMaze().GetDeadEnds())
  {
    if (Get(p.first,p.second) == MazeSquare::msExit) return p;
  }
  assert(!"Maze guarantees to have an exit");
  return {0, 0};
}

std::pair<int,int> ribi::maziak::Maze::FindStart() const noexcept
{
  for (std::pair<int,int> p: GetIntMaze().GetDeadEnds())
  {
    if (Get(p.first,p.second) == MazeSquare::msStart) return p;
  }
  assert(!"Maze guarantees to have a start");
  return {0, 0};
}

ribi::maziak::MazeSquare ribi::maziak::Maze::Get(
  const int x, const int y) const
{
  Expects(CanGet(x,y));
  return m_maze[y][x];
}

int ribi::maziak::GetSize(const Maze& m) noexcept
{
  return GetSize(m.GetIntMaze());
}

bool ribi::maziak::IsSquare(const Maze& m)
{
  return IsSquare(m.GetIntMaze());
}

void ribi::maziak::Maze::Set(const int x, const int y, const MazeSquare s)
{
  Expects(CanSet(x,y));
  m_maze[y][x] = s;
  Ensures(Get(x,y) == s);
}

std::ostream& ribi::maziak::operator<<(
  std::ostream& os, const Maze& m) noexcept
{
  os << "IntMaze:\n" << m.m_int_maze << '\n';
  os << "Maze:\n" << m.m_maze;
  return os;
}

std::string ribi::maziak::ToStr(const Maze& m) noexcept
{
  std::stringstream s;
  s << m;
  return s.str();
}

std::string ribi::maziak::ToStr(const std::vector<std::vector<MazeSquare>>& m) noexcept
{
  std::stringstream s;
  s << m;
  return s.str();
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
