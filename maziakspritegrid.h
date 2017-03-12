#ifndef MAZIAKSPRITEGRID_H
#define MAZIAKSPRITEGRID_H

#include <vector>
#include "maziaksprite.h"

namespace ribi {
namespace maziak {

///SpriteGrid is a 3D grid of Sprites:
///
/// For example:
///
/// XXXX
/// X123
/// X4XX
///
/// X = { wall }
/// 1 = { floor, solutionpath, player }
/// 2 = { floor, solutionpath }
/// 3 = { floor, solutionpath, enemy }
/// 4 = { floor }
struct SpriteGrid
{
  SpriteGrid(const int ncols, const int nrows);

  std::vector<Sprite> Get(const int x, const int y) const noexcept;

  private:
  std::vector<std::vector<std::vector<Sprite>>> m_v;

};

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKSPRITEGRID_H
