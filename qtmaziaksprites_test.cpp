#include "maziaksprites.h"

#include <boost/test/unit_test.hpp>
#include <QPixmap>

#include "maziakhelper.h"
#include "qtgraphics.h"

using namespace ribi::maziak;

BOOST_AUTO_TEST_CASE(maziak_CreateSprites)
{
  const auto m = CreateSprites();
  for (const auto& p: m)
  {
    const QPixmap& pixmap = p.second;
    BOOST_CHECK_EQUAL(pixmap.width(), Sprites().GetWidth());
    BOOST_CHECK_EQUAL(pixmap.height(), Sprites().GetHeight());
    BOOST_CHECK(::ribi::IsValidFormat(pixmap.toImage().format()));
  }
}
