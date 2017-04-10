#ifndef MAZIAKINTMAZE_H
#define MAZIAKINTMAZE_H

#include <iosfwd>
#include <vector>

#include "maziakcoordinat.h"
#include "maziakfwd.h"
#include "maziakintgrid.h"

namespace ribi {
namespace maziak {

///A maze using integers
/// 0 : path
/// 1 : wall
struct IntMaze
{
  explicit IntMaze();
  explicit IntMaze(
    const int n_cols,
    const int n_rows,
    const int rng_seed
  );
  explicit IntMaze(const IntGrid& int_grid);

  ///Can I access this coordinat?
  bool CanGet(const Coordinat c) const noexcept;

  ///Read the coordinat
  int Get(const Coordinat c) const noexcept;

  ///Read the raw grid
  const auto& Get() const noexcept { return m_int_grid; }

  private:
  IntGrid m_int_grid;
  friend std::ostream& operator<<(std::ostream& os, const IntMaze& m) noexcept;
};

///Collect all dead ends
std::vector<Coordinat> CollectDeadEnds(const IntGrid& grid) noexcept;
std::vector<Coordinat> CollectDeadEndsImpl1(const IntGrid& grid) noexcept;
std::vector<Coordinat> CollectDeadEndsImpl2(const IntGrid& grid) noexcept;

///Collect all dead ends
std::vector<Coordinat> CollectDeadEnds(const IntMaze& maze) noexcept;


///Count the occurance of i in the IntMaze
int Count(const int i, const IntMaze& m);

DistancesMaze CreateDistancesMaze(
  const IntMaze& m,
  const Coordinat target
);

IntMaze CreateIntMaze(
  const int n_cols,
  const int n_rows,
  const int seed
);

int get_n_cols(const IntMaze& m) noexcept;
int get_n_rows(const IntMaze& m) noexcept;

bool operator==(const IntMaze& lhs, const IntMaze& rhs) noexcept;

std::ostream& operator<<(std::ostream& os, const IntMaze& m) noexcept;

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKINTMAZE_H
