#include "qtmaziakdisplay_test.h"
#include "qtmaziakdisplay.h"
#include "maziakgame.h"

void ribi::maziak::QtDisplay_test::view_width_is_nine()
{
  QtDisplay q;
  //Cannot test this in constructor: never call virtual functions in a class constructor
  assert(q.GetViewHeight() == 9);
  assert(q.GetViewWidth() == 9);
}

void ribi::maziak::QtDisplay_test::display()
{
  QtDisplay q;
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
