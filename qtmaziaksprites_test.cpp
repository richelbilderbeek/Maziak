#include "qtmaziaksprites_test.h"
#include "qtmaziaksprites.h"
#include "maziaksprites.h"
#include "qtgraphics.h"

void ribi::maziak::QtSprites_test::all_sprites_are_present()
{
  Sprites s;
  for (const auto i: GetAllSprites())
  {
    const QPixmap pixmap = s.Get(i);
    QVERIFY(pixmap.width() == GetSpriteWidth());
    QVERIFY(pixmap.height() == GetSpriteHeight());
    QVERIFY(::ribi::IsValidFormat(pixmap.toImage().format()));
  }
}

void ribi::maziak::QtSprites_test::images_are_correct()
{
  const auto m = CreateSprites();
  for (const auto& p: m)
  {
    const QPixmap& pixmap = p.second;
    QVERIFY(pixmap.width() == GetSpriteWidth());
    QVERIFY(pixmap.height() == GetSpriteHeight());
    QVERIFY(::ribi::IsValidFormat(pixmap.toImage().format()));
  }
}

