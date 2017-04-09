#ifndef MAZIAKHELPER_H
#define MAZIAKHELPER_H

#include <algorithm>
#include <cassert>
#include <numeric>
#include <vector>
#include <gsl/gsl_assert>
#include "maziakcoordinat.h"
#include "maziakmazesquare.h"

namespace ribi {
namespace maziak {

std::string CamelCasify(const std::string& s) noexcept;

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

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKHELPER_H
