#include "maziakdistancesmaze.h"

#include <cassert>

#include "maziakintmaze.h"

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

std::vector<std::vector<int>> ribi::maziak::CalculateDistances(
  const IntMaze& maze,
  const int x, const int y) noexcept
{
  //Assume maze is square
  assert(maze.IsSquare());
  assert(maze.Get(x,y) == 0); //Assume starting point is no wall

  const int size = maze.GetSize();
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

        if (maze.Get(x_here,y_here-1) == 0                //No wall
          && distances[y_here-1][x_here] == maxDistance) //Not already in solution
        {
          distances[y_here-1][x_here] = distance;
          newFound.push_back(std::make_pair(x_here,y_here-1));
        }
        if (maze.Get(x_here,y_here+1) == 0                //No wall
          && distances[y_here+1][x_here] == maxDistance) //Not already in solution
        {
          distances[y_here+1][x_here] = distance;
          newFound.push_back(std::make_pair(x_here,y_here+1));
        }

        if (maze.Get(x_here+1,y_here) == 0                //No wall
          && distances[y_here][x_here+1] == maxDistance) //Not already in solution
        {
          distances[y_here][x_here+1] = distance;
          newFound.push_back(std::make_pair(x_here+1,y_here));
        }

        if (maze.Get(x_here-1,y_here) == 0                //No wall
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

