#include "maziakdistancesmaze.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <numeric>

#include "maziakintmaze.h"
#include "maziakmaze.h"

ribi::maziak::DistancesMaze::DistancesMaze()
  : m_distances{}
{

}

ribi::maziak::DistancesMaze::DistancesMaze(
  const IntMaze& maze,
  const int x,
  const int y
  )
  : m_distances(CalculateDistances(maze,x,y))
{

}

ribi::maziak::DistancesMaze::DistancesMaze(
  const Maze& maze,
  const int x,
  const int y
  )
  : m_distances(CalculateDistances(maze,x,y))
{

}

ribi::maziak::DistancesMaze::DistancesMaze(
  const Maze& maze,
  const std::pair<int, int> p
  )
  : m_distances(CalculateDistances(maze,p.first,p.second))
{

}

std::vector<std::vector<int>> ribi::maziak::CalculateDistances(
  const IntMaze& maze,
  const int x, const int y) noexcept
{
  assert(maze.Get(x,y) == 0); //Assume starting point is no wall

  const int size = get_n_rows(maze);
  const int area = size * size;
  const int maxDistance = area;
  std::vector<std::vector<int>> distances(size, std::vector<int>(size,maxDistance));
  {
    //Calculate the distances
    int distance = 0;
    distances[y][x] = 0; //Set final point
    std::vector<std::pair<int,int>> found = { {x,y} };

    while(!found.empty())
    {
      ++distance;
      std::vector< std::pair<int,int> > newFound;

      for (const auto& p: found)
      {
        const int x_here{p.first};
        const int y_here{p.second};
        const std::vector<std::pair<int,int>> deltas = {
          {  0, +1 },
          { +1,  0 },
          {  0, -1 },
          { -1,  0 }
        };
        for (const auto& d: deltas)
        {
          if (maze.Get(x_here + d.first,y_here + d.second) == 0                //No wall
            && distances[y_here + d.second][x_here + d.first] == maxDistance) //Not already in solution
          {
            distances[y_here + d.second][x_here + d.first] = distance;
            newFound.push_back(std::make_pair(x_here + d.first,y_here + d.second));
          }
        }
      }
      found = newFound;
    }
  }
  return distances;
}

std::vector<std::vector<int>> ribi::maziak::CalculateDistances(
  const Maze& maze,
  const int x, const int y) noexcept
{
  //Assume maze is square
  assert(maze.Get(x,y) != MazeSquare::msWall); //Assume starting point is no wall

  const int size = get_n_rows(maze);
  const int area = size * size;
  const int maxDistance = area;
  std::vector<std::vector<int> > distances(size, std::vector<int>(size,maxDistance));
  {
    //Calculate the distances
    int distance = 0;
    distances[y][x] = 0; //Set final point
    std::vector< std::pair<int,int> > found;
    found.push_back(std::make_pair(x,y));

    while(found.empty() == false)
    {
      ++distance;
      std::vector< std::pair<int,int> > newFound;

      const std::vector< std::pair<int,int> >::iterator j = found.end();
      for (std::vector< std::pair<int,int> >::iterator i = found.begin(); i!=j; ++i)
      {
        const int x_here{(*i).first};
        const int y_here{(*i).second};

        if (maze.Get(x_here,y_here-1) != MazeSquare::msWall
          && distances[y_here-1][x_here] == maxDistance) //Not already in solution
        {
          distances[y_here-1][x_here] = distance;
          newFound.push_back(std::make_pair(x_here,y_here-1));
        }
        if (maze.Get(x_here,y_here+1) != MazeSquare::msWall
          && distances[y_here+1][x_here] == maxDistance) //Not already in solution
        {
          distances[y_here+1][x_here] = distance;
          newFound.push_back(std::make_pair(x_here,y_here+1));
        }

        if (maze.Get(x_here+1,y_here) != MazeSquare::msWall
          && distances[y_here][x_here+1] == maxDistance) //Not already in solution
        {
          distances[y_here][x_here+1] = distance;
          newFound.push_back(std::make_pair(x_here+1,y_here));
        }

        if (maze.Get(x_here-1,y_here) != MazeSquare::msWall
          && distances[y_here][x_here-1] == maxDistance) //Not already in solution
        {
          distances[y_here][x_here-1] = distance;
          newFound.push_back(std::make_pair(x_here-1,y_here));
        }

      }
      found = newFound;
    }
  }
  return distances;
}

bool ribi::maziak::DistancesMaze::CanGet(const int x, const int y) const noexcept
{
  return x >= 0 && x < GetSize()
      && y >= 0 && y < GetSize();
}

int ribi::maziak::DistancesMaze::Get(const int x, const int y) const noexcept
{
  assert(CanGet(x,y));
  return m_distances[y][x];
}

int ribi::maziak::DistancesMaze::GetSize() const noexcept
{
  return ::ribi::maziak::get_n_rows(*this);
}

int ribi::maziak::get_n_rows(const DistancesMaze& m) noexcept
{
  return static_cast<int>(m.Get().size());
}

std::ostream& ribi::maziak::operator<<(
  std::ostream& os, const DistancesMaze& m) noexcept
{
  const auto& v = m.Get();
  std::transform(
    std::begin(v),
    std::end(v),
    std::ostream_iterator<std::string>(os, "\n"),
    [](const auto& row)
    {
      return std::accumulate(
        std::begin(row),
        std::end(row),
        std::string(),
        [](std::string init, const int i)
        {
          return init + std::to_string(i);
        }
      );
    }
  );
  return os;
}
