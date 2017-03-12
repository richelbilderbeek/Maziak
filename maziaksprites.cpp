#include "maziaksprites.h"

#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <gsl/gsl_assert>
#include <QPixmap>
#include <QImage>
#include "maziakhelper.h"
#include "qtgraphics.h"

template <class T, class P>
bool all(const T& v, const P& p)
{
  return std::all_of(std::begin(v), std::end(v), p);
}

ribi::maziak::Sprites::Sprites()
  : m_sprites(CreateSprites())
{
  Ensures(
    all(
      GetAllSprites(),
      [this](const Sprite s)
      {
        return ::ribi::IsValidFormat(this->Get(s).toImage().format());
      }
    )
  );
}


std::map<ribi::maziak::Sprite,QPixmap> ribi::maziak::CreateSprites() noexcept
{
  std::map<ribi::maziak::Sprite,QPixmap> m;
  const std::vector<Sprite> v { GetAllSprites() };
  for (const Sprite sprite: v)
  {
    std::string spritename { ToStr(sprite) };
    spritename[0] = std::toupper(spritename[0]);
    spritename = CamelCasify(spritename);

    const std::string filename {
      ":/images/" + spritename + ".png"
    };
    QPixmap pixmap{filename.c_str()};
    assert(pixmap.width() > 0);
    assert(pixmap.height() > 0);
    if (!IsValidFormat(pixmap.toImage().format()))
    {
      pixmap = QPixmap::fromImage(
        pixmap.toImage().convertToFormat(QImage::Format::Format_ARGB32),
        Qt::NoFormatConversion);
      assert(IsValidFormat(pixmap.toImage().format()));
    }
    assert(IsValidFormat(pixmap.toImage().format()));
    assert(pixmap.width() == Sprites().GetWidth());
    assert(pixmap.height() == Sprites().GetHeight());
    m.insert(std::make_pair(sprite,pixmap));
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

std::vector<ribi::maziak::Sprite> ribi::maziak::GetAllSprites() noexcept
{
  const std::vector<Sprite> v {
    Sprite::empty,
    Sprite::wall,
    Sprite::path,
    Sprite::transparent,
    Sprite::player_look_down,
    Sprite::player_look_down_sword,
    Sprite::player_look_left,
    Sprite::player_look_left_sword,
    Sprite::player_look_right,
    Sprite::player_look_right_sword,
    Sprite::player_look_up,
    Sprite::player_look_up_sword,
    Sprite::player_walk_left1,
    Sprite::player_walk_left2,
    Sprite::player_walk_left_sword1,
    Sprite::player_walk_left_sword2,
    Sprite::player_walk_right1,
    Sprite::player_walk_right2,
    Sprite::player_walk_right_sword1,
    Sprite::player_walk_right_sword2,
    Sprite::player_walk_down1,
    Sprite::player_walk_down2,
    Sprite::player_walk_down_sword1,
    Sprite::player_walk_down_sword2,
    Sprite::player_walk_up1,
    Sprite::player_walk_up2,
    Sprite::player_walk_up_sword1,
    Sprite::player_walk_up_sword2,
    Sprite::player_won1,
    Sprite::player_won2,
    Sprite::fight_sword1,
    Sprite::fight_no_sword1,
    Sprite::fight2,
    Sprite::fight3,
    Sprite::fight4,
    Sprite::fight_won1,
    Sprite::fight_won2,
    Sprite::fight_lost1,
    Sprite::fight_lost2,
    Sprite::enemy1,
    Sprite::enemy2,
    Sprite::prisoner1,
    Sprite::prisoner2,
    Sprite::sword,
    Sprite::exit
  };
  assert(static_cast<int>(v.size()) == static_cast<int>(Sprite::n_sprites)
    && "All Sprite values (except Sprite::n_sprites) must be in");

  return v;
}


