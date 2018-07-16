#ifndef QTMAZIAKSPRITES_H
#define QTMAZIAKSPRITES_H

#include <vector>
#include <map>



#include <QImage>
#include "maziaksprite.h"


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
