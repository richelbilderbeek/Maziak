#ifndef MAZIAKSPRITES_H
#define MAZIAKSPRITES_H

#include <vector>
#include <map>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "maziaksprite.h"
#pragma GCC diagnostic pop

struct QPixmap;

namespace ribi {
namespace maziak {

struct Sprites
{
  Sprites();
  const QPixmap& Get(const Sprite sprite) const noexcept;

  ///ASCII art
  static char ToChar(const Sprite) noexcept;

  private:
  const std::map<Sprite,QPixmap> m_sprites;

  static std::string CamelCasify(const std::string& s) noexcept;
  std::map<Sprite,QPixmap> CreateSprites() noexcept;
  static std::vector<Sprite> GetAllSprites() noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  static std::string ToStr(const Sprite) noexcept;
};

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKSPRITES_H
