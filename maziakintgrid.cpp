#include "maziakintgrid.h"

#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <gsl/gsl_assert>

#include "maziakhelper.h"

ribi::maziak::IntGrid
  ribi::maziak::CreateIntGrid(const int sz,
  const int rng_seed
)
{
  Expects(IsValidSize(sz));
  std::mt19937 rng_engine{rng_seed};

  //Start with a wall-only maze
  std::vector<std::vector<int> > maze(sz, std::vector<int>(sz,1));

  //Prepare maze, remove paths
  // XXXXXXX    1111111
  // X X X X    1212121
  // XXXXXXX    1111111
  // X XOX X -> 1210121
  // XXXXXXX    1111111
  // X X X X    1212121
  // XXXXXXX    1111111

  //Draw open spaces
  for (int y=1; y<sz; y+=2)
  {
    for (int x=1; x<sz; x+=2)
    {
      maze[y][x] = 2; //2: unexplored
    }
  }

  const int mid = sz/2;

  maze[mid][mid] = 0;

  std::vector<std::pair<int,int> > v;
  v.push_back(std::make_pair(mid,mid));
  while (!v.empty())
  {
    std::uniform_int_distribution<int> d_next_explorer(0, v.size() - 1); //-1 as this is inclusive

    //Set a random explorer square at the back
    //std::swap(v.back(),v[ std::rand() % static_cast<int>(v.size())]);
    const int next_explorer{d_next_explorer(rng_engine)};
    assert(next_explorer >= 0);
    assert(next_explorer < static_cast<int>(v.size()));
    std::swap(v.back(),v[next_explorer]);
    //Check possible adjacent squares
    const int x = v.back().first;
    const int y = v.back().second;
    std::vector<std::pair<int,int> > next;
    if (x > 0 + 2 && maze[y][x-2] == 2) next.push_back(std::make_pair(x-2,y));
    if (y > 0 + 2 && maze[y-2][x] == 2) next.push_back(std::make_pair(x,y-2));
    if (x < sz - 2 && maze[y][x+2] == 2) next.push_back(std::make_pair(x+2,y));
    if (y < sz - 2 && maze[y+2][x] == 2) next.push_back(std::make_pair(x,y+2));
    //Dead end?
    if (next.empty())
    {
      v.pop_back();
      continue;
    }
    //Select a random next adjacent square
    std::uniform_int_distribution<int> d_next_index(0, next.size() - 1); //-1 as this is inclusive

    const int nextIndex{d_next_index(rng_engine)};
    //const int nextIndex = (std::rand() >> 4) % static_cast<int>(next.size());
    assert(nextIndex >= 0);
    assert(nextIndex < static_cast<int>(next.size()));
    const int nextX = next[nextIndex].first;
    const int nextY = next[nextIndex].second;
    //Clear next square
    maze[nextY][nextX] = 0;
    //Clear path towards next square
    maze[(y + nextY)/2][(x + nextX)/2] = 0;
    //Add next square to stack
    v.push_back(std::make_pair(nextX,nextY));
  }
  return maze;
}

int ribi::maziak::GetSize(const IntGrid& g) noexcept
{
  return static_cast<int>(g.size());
}

bool ribi::maziak::IsValidSize(const int sz) noexcept
{
  return sz >= 7 && sz % 4 == 3;
}

std::ostream& ribi::maziak::operator<<(
  std::ostream& os, const IntGrid& v) noexcept
{
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


