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
  const Coordinat c
)
  : m_distances(CalculateDistances(maze,c))
{

}

ribi::maziak::DistancesMaze::DistancesMaze(
  const Maze& maze,
  const Coordinat c
  )
  : m_distances(CalculateDistances(maze, c))
{

}

std::vector<std::vector<int>> ribi::maziak::CalculateDistances(
  const IntMaze& maze,
  const Coordinat c
  ) noexcept
{
  assert(maze.Get(c) == 0); //Assume starting point is no wall

  const int n_rows = get_n_rows(maze);
  const int n_cols = get_n_rows(maze);
  const int area = n_rows * n_cols;
  const int maxDistance = area;
  std::vector<std::vector<int>> distances(n_rows, std::vector<int>(n_cols, maxDistance));
  {
    //Calculate the distances
    int distance = 0;
    const auto x = get_x(c);
    const auto y = get_y(c);
    distances[y][x] = 0; //Set final point
    std::vector<Coordinat> found = { {x,y} };

    while(!found.empty())
    {
      ++distance;
      std::vector<Coordinat> newFound;

      for (const auto& p: found)
      {
        const auto adjacent = get_adjacent_4(c);
        for (const auto& d: adjacent)
        {
          //No wall and
          //not already in solution
          if (maze.Get(d) == 0
            && distances[get_y(d)][get_x(d)] == maxDistance)

          {
            distances[get_y(d)][get_x(d)] = distance;
            newFound.push_back(d);
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
  const Coordinat goal) noexcept
{
  assert(maze.Get(goal) != MazeSquare::wall);

  const int n_rows = get_n_rows(maze);
  const int n_cols = get_n_cols(maze);
  const int area = n_rows * n_cols;
  const int maxDistance = area;
  std::vector<std::vector<int>> distances(n_rows, std::vector<int>(n_cols,maxDistance));
  {
    //Calculate the distances
    int distance = 0;
    distances[get_y(goal)][get_x(goal)] = 0; //Set final point
    std::vector<Coordinat> found;
    found.push_back(goal);

    while(found.empty() == false)
    {
      ++distance;
      std::vector<Coordinat> newFound;

      for (const Coordinat c: found)
      {
        const auto adjacent = get_adjacent_4(c);
        for (const Coordinat d: adjacent)
        {
          if (maze.CanGet(d)
            && maze.Get(d) != MazeSquare::wall
            && distances[get_y(d)][get_x(d)] == maxDistance) //Not already in solution
          {
            distances[get_y(d)][get_x(d)] = distance;
            newFound.push_back(d);
          }
        }
      }
      found = newFound;
    }
  }
  return distances;
}

bool ribi::maziak::DistancesMaze::CanGet(const Coordinat c) const noexcept
{
  const auto x = get_x(c);
  const auto y = get_y(c);
  return x >= 0 && x < get_n_cols(*this)
      && y >= 0 && y < get_n_rows(*this)
  ;
}

int ribi::maziak::DistancesMaze::Get(const Coordinat c) const noexcept
{
  assert(CanGet(c));
  const auto x = get_x(c);
  const auto y = get_y(c);
  return m_distances[y][x];
}

int ribi::maziak::get_n_cols(const DistancesMaze& m) noexcept
{
  assert(!m.Get().empty());
  return static_cast<int>(m.Get()[0].size());
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
