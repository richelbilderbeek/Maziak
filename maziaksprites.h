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

struct Sprites
{
  Sprites();
  const QPixmap& Get(const Sprite sprite) const noexcept;

  ///ASCII art
  static char ToChar(const Sprite) noexcept;

  private:
  const std::map<Sprite,QPixmap> m_sprites;

  //assert(CamelCasify("player_look_down_sword") == "playerLookDownSword");
  std::map<Sprite,QPixmap> CreateSprites() noexcept;
};

std::string CamelCasify(const std::string& s) noexcept;

std::vector<Sprite> GetAllSprites() noexcept;

///Determines if the image format is correct
bool IsValidFormat(const QImage::Format format) noexcept;

std::string ToStr(const Sprite) noexcept;


} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKSPRITES_H
