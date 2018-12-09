#include "qtmaziaksprites.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <gsl/gsl_assert>
#include <QPixmap>
#include <QImage>
#include "maziakhelper.h"

template <class T, class P>
bool all(const T& v, const P& p)
{
  return std::all_of(std::begin(v), std::end(v), p);
}

ribi::maziak::Sprites::Sprites()
  : m_sprites(CreateSprites())
{

}


std::map<ribi::maziak::Sprite,QPixmap> ribi::maziak::CreateSprites() noexcept
{
  std::map<Sprite,QPixmap> m;
  for (const Sprite sprite: get_all_sprites())
  {
    std::string spritename { to_str(sprite) };
    spritename[0] = std::toupper(spritename[0]);
    spritename = CamelCasify(spritename);

    const std::string filename {
      ":/maziak/pics/" + spritename + ".png"
    };
    QPixmap pixmap{filename.c_str()};
    m.insert( { sprite,pixmap });
  }
  return m;
}

const QPixmap& ribi::maziak::Sprites::Get(const Sprite sprite) const noexcept
{
  assert(m_sprites.find(sprite) != m_sprites.end());
  const QPixmap& pixmap {
    m_sprites.find(sprite)->second
  };
  return pixmap;
}
