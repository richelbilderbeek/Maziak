#ifndef QTMAZIAKSPRITES_H
#define QTMAZIAKSPRITES_H

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

///Lookuptable for sprites
struct Sprites
{
  Sprites();
  const QPixmap& Get(const Sprite sprite) const noexcept;

  private:
  const std::map<Sprite,QPixmap> m_sprites;
};

constexpr int GetSpriteHeight() { return 24; }
constexpr int GetSpriteWidth() { return 24; }

///Create a Sprite to QPixmap lookup table
std::map<Sprite,QPixmap> CreateSprites() noexcept;

} //~namespace maziak
} //~namespace ribi

#endif // QTMAZIAKSPRITES_H
