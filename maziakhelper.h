#ifndef MAZIAKHELPER_H
#define MAZIAKHELPER_H

#include <cassert>
#include <vector>
#include <gsl/gsl_assert>
#include "maziakmazesquare.h"

namespace ribi {
namespace maziak {

const std::vector<std::pair<int,int>> GetShuffledDeadEnds(
    const std::vector<std::vector<int>>& intMaze);

const std::vector<std::pair<int,int>> GetShuffledNonDeadEnds(
    const std::vector<std::vector<int>>& intMaze);

bool CanMoveTo(
    const std::vector<std::vector<MazeSquare> >& maze,
    const int x, const int y,
    const bool hasSword,
    const bool showSolution);

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
  for(const std::vector<T>& row: v)
  {
    if (row.size() != v.size()) return false;
  }
  return true;
}


} //~namespace maziak
} //~namespace ribi


#endif // MAZIAKHELPER_H
