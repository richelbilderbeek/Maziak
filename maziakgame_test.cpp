#include "maziakgame.h"

#include <boost/test/unit_test.hpp>

#include "maziaksprite.h"

using namespace ribi::maziak;

BOOST_AUTO_TEST_CASE(maziak_MainDialog_construction)
{
  const Game g{CreateTestMaze1()};
  BOOST_CHECK(!g.GetDoShowSolution());
}

BOOST_AUTO_TEST_CASE(maziak_MainDialog_stream_out)
{
  const Game g{CreateTestMaze1()};
  std::stringstream s;
  s << g;
  const auto t = to_str(g);
  BOOST_CHECK(!s.str().empty());
  BOOST_CHECK_EQUAL(s.str(), t);
}

BOOST_AUTO_TEST_CASE(maziak_CreateTestMainDialog1)
{
  const auto g = CreateTestGame1();
  const auto m1 = g.GetMaze().Get();
  const auto m2 = CreateTestMaze1().Get();
  BOOST_CHECK_EQUAL(m1, m2);
}


BOOST_AUTO_TEST_CASE(maziak_game_can_get_sprites)
{
/*

    012345678901234
  0 XXXXXXXXXXXXXXX
  1 X  +X+    X+  X
  2 X XXXXX XXXXX X
  3 X    ZX X  +X X
  4 XXX XXX X XXX X
  5 X:X X.X   XZ  X
  6 X X X X XXXXX X
  7 X             X
  8 XXXXX X X XXX X
  9 X     X X  ZX X
  0 X XXX X X XXXXX
  1 X   X X!X   X X
  2 XXX X XXXXX X X
  3 X   X     X   X
  4 XXXXXXXXXXXXXXX

*/
  const auto g = CreateTestGame1();
  {
    const auto measured = g.GetSprites(0,0);
    const auto expected = { Sprite::wall };
    std::copy(std::begin(measured), std::end(measured),
      std::ostream_iterator<Sprite>(std::cerr, ", "));
    BOOST_CHECK_EQUAL_COLLECTIONS(
      std::begin(expected), std::end(expected),
      std::begin(measured), std::end(measured)
    );
  }
  {
    const auto measured = g.GetSprites(1,1);
    const auto expected = { Sprite::empty };
    BOOST_CHECK_EQUAL_COLLECTIONS(
      std::begin(expected), std::end(expected),
      std::begin(measured), std::end(measured)
    );
  }
  {
    const auto measured = g.GetSprites(3,1);
    const auto expected = { Sprite::sword };
    BOOST_CHECK_EQUAL_COLLECTIONS(
      std::begin(expected), std::end(expected),
      std::begin(measured), std::end(measured)
    );
  }
}
