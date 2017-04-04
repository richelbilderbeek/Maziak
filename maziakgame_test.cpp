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
  //Wall in maze
  {
    const auto measured = g.GetSprites(2, 2);
    const auto expected = { Sprite::wall };
    BOOST_CHECK_EQUAL_COLLECTIONS(
      std::begin(expected), std::end(expected),
      std::begin(measured), std::end(measured)
    );
  }
  //Wall out of maze
  {
    const auto measured = g.GetSprites(-2, -2);
    const auto expected = { Sprite::wall };
    BOOST_CHECK_EQUAL_COLLECTIONS(
      std::begin(expected), std::end(expected),
      std::begin(measured), std::end(measured)
    );
  }
  //Road
  {
    const auto measured = g.GetSprites(1, 1);
    const auto expected = { Sprite::empty };
    BOOST_CHECK_EQUAL_COLLECTIONS(
      std::begin(expected), std::end(expected),
      std::begin(measured), std::end(measured)
    );
  }
  //Sword
  {
    const auto measured = g.GetSprites(3, 1);
    const auto expected = { Sprite::sword };
    BOOST_CHECK_EQUAL_COLLECTIONS(
      std::begin(expected), std::end(expected),
      std::begin(measured), std::end(measured)
    );
  }
  //Prisoner 1
  {
    const int prisoner_frame{0};
    const auto measured = g.GetSprites(1, 5, prisoner_frame);
    const auto expected = { Sprite::prisoner1 };
    BOOST_CHECK_EQUAL_COLLECTIONS(
      std::begin(expected), std::end(expected),
      std::begin(measured), std::end(measured)
    );
  }
  //Prisoner 2
  {
    const int prisoner_frame{1};
    const auto measured = g.GetSprites(1, 5, prisoner_frame);
    const auto expected = { Sprite::prisoner2 };
    BOOST_CHECK_EQUAL_COLLECTIONS(
      std::begin(expected), std::end(expected),
      std::begin(measured), std::end(measured)
    );
  }
  //Enemy 1
  {
    const int prisoner_frame{0};
    const auto measured = g.GetSprites(5, 3, prisoner_frame);
    const auto expected = { Sprite::enemy1 };
    BOOST_CHECK_EQUAL_COLLECTIONS(
      std::begin(expected), std::end(expected),
      std::begin(measured), std::end(measured)
    );
  }
  //Enemy 2
  {
    const int prisoner_frame{1};
    const auto measured = g.GetSprites(5, 3, prisoner_frame);
    const auto expected = { Sprite::enemy2 };
    BOOST_CHECK_EQUAL_COLLECTIONS(
      std::begin(expected), std::end(expected),
      std::begin(measured), std::end(measured)
    );
  }


  //std::copy(std::begin(measured), std::end(measured),
  // std::ostream_iterator<Sprite>(std::cerr, ", "));
}
