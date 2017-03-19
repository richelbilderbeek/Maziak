#ifndef MAZIAKHELPER_H
#define MAZIAKHELPER_H

#include <algorithm>
#include <cassert>
#include <numeric>
#include <vector>
#include <gsl/gsl_assert>
#include "maziakmazesquare.h"

namespace ribi {
namespace maziak {

std::string CamelCasify(const std::string& s) noexcept;

bool CanMoveTo(
  const std::vector<std::vector<MazeSquare> >& maze,
  const int x, const int y,
  const bool hasSword,
  const bool showSolution);

///2D version of std::count
template <class T>
int Count(const T i, const std::vector<std::vector<T>>& m)
{
  return std::accumulate(
    std::begin(m),
    std::end(m),
    0,
    [i](int init, const auto& row)
    {
      return init + std::count(std::begin(row), std::end(row), i);
    }
  );
}


///Get the coordinats where the end ends are
//From http://www.richelbilderbeek.nl/CppGetDeadEnds.htm
std::vector<std::pair<int,int>> GetDeadEnds(const std::vector<std::vector<int>>& maze);

///Get the distances it would be to travel from (x,y) to
///any location in the maze
/*

 456789
 3
 21012 8
   1 3 7
 4323456

*/
//From http://www.richelbilderbeek.nl/CppGetMazeDistances.htm
std::vector<std::vector<int>> GetMazeDistances(
    const std::vector<std::vector<int>>& maze,
    const int x,
    const int y);


template <class T>
bool IsSquare(const std::vector<std::vector<T>>& v)
{
  Expects(!v.empty());
  return std::all_of(
    std::begin(v), std::end(v),
    [v](const auto& row)
    {
      return row.size() == v.size();
    }
  );
}




} //~namespace maziak
} //~namespace ribi


#endif // MAZIAKHELPER_H
