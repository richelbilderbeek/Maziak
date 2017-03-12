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

  ///ASCII art
  static char ToChar(const Sprite) noexcept;

  int GetHeight() const noexcept { return 24; }
  int GetWidth() const noexcept { return 24; }

  private:
  const std::map<Sprite,QPixmap> m_sprites;

  //assert(CamelCasify("player_look_down_sword") == "playerLookDownSword");
  std::map<Sprite,QPixmap> CreateSprites() noexcept;
};

std::string CamelCasify(const std::string& s) noexcept;

std::vector<Sprite> GetAllSprites() noexcept;

std::string ToStr(const Sprite) noexcept;


} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKSPRITES_H
