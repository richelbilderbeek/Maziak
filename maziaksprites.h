#ifndef MAZIAKSPRITES_H
#define MAZIAKSPRITES_H

#include <vector>
#include <map>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QImage>
#include "maziaksprite.h"
#pragma GCC diagnostic pop

struct QPixmap;

namespace ribi {
namespace maziak {

///Loads all 24x24 sprites
struct Sprites
{
  Sprites();
  const QPixmap& Get(const Sprite sprite) const noexcept;

  int GetHeight() const noexcept { return 24; }
  int GetWidth() const noexcept { return 24; }

  private:
  const std::map<Sprite,QPixmap> m_sprites;

};

///Create a Sprite to QPixmap lookup table
std::map<Sprite,QPixmap> CreateSprites() noexcept;

std::vector<Sprite> GetAllSprites() noexcept;

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKSPRITES_H
