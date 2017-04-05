#include "qtmaziakdisplay_test.h"
#include "qtmaziakdisplay.h"
#include "maziakgame.h"

void ribi::maziak::QtDisplay_test::view_width_is_nine()
{
  const int view_width{11};
  const int view_height{13};
  QtDisplay q(view_width, view_height);
  //Cannot test this in constructor: never call virtual functions in a class constructor
  QVERIFY(q.GetViewHeight() == view_height);
  QVERIFY(q.GetViewWidth() == view_width);
}

void ribi::maziak::QtDisplay_test::display()
{
  QtDisplay q(13,15);
  q.show();
}

/*
void ribi::maziak::QtDisplay_test::display()
{
  QtDisplay q;
  const auto sprites = q.GetSprites();
  Expects(m_image.height() == GetSpriteHeight() * GetViewHeight());
  Expects(m_image.width() == GetSpriteWidth() * GetViewWidth());
}
*/
