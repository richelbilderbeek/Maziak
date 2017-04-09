#include "maziakgame.h"

#include <iostream>
#include <boost/test/unit_test.hpp>

#include "maziaksprite.h"

using namespace ribi::maziak;

BOOST_AUTO_TEST_CASE(maziak_CreateTestGame1)
{
  const Game g{CreateTestGame1()};
  BOOST_CHECK(!g.GetDoShowSolution());
}

BOOST_AUTO_TEST_CASE(maziak_Game_construction)
{
  const auto n_cols = 15;
  const auto n_rows = 11;
  const int rng_seed{145};
  const Game g{Maze{n_cols, n_rows, rng_seed}};
  BOOST_CHECK_EQUAL(n_cols, get_n_cols(g));
  BOOST_CHECK_EQUAL(n_rows, get_n_rows(g));
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


BOOST_AUTO_TEST_CASE(maziak_game_can_get_sprites_no_path)
{
/*
    0123456789012345678

 0  XXXXXXXXXXXXXXXXXXX
 1  X!  X X+X.      X X
 2  XXX X X XXX XXXXX X
 3  XZX X X XZ  X:X X X
 4  X X X X XXX X X X X
 5  X   X X         X X
 6  X XXX XXX XXXXXXX X
 7  X                 X
 8  X X XXXXX XXX XXXXX
 9  X X X X X  +X     X
10  X XXX XXX XXX XXXXX
11  X X         X     X
12  X X X X XXX XXXXX X
13  X X+X X+X    ZX   X
14  XXXXXXXXXXXXXXXXXXX

*/

  const Game g{CreateTestGame1()};
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
    const auto measured = g.GetSprites(2, 1);
    const auto expected = { Sprite::empty };
    BOOST_CHECK_EQUAL_COLLECTIONS(
      std::begin(expected), std::end(expected),
      std::begin(measured), std::end(measured)
    );
  }
  //Sword
  {
    const auto measured = g.GetSprites(7, 1);
    const auto expected = { Sprite::sword };
    BOOST_CHECK_EQUAL_COLLECTIONS(
      std::begin(expected), std::end(expected),
      std::begin(measured), std::end(measured)
    );
  }
  //Start should not be visible, but player on it is
  {
    assert(g.GetMaze().Get(9, 1) == MazeSquare::start);
    const auto measured = g.GetSprites(9, 1);
    const auto expected = { Sprite::player_look_down_sword };
    BOOST_CHECK_EQUAL_COLLECTIONS(
      std::begin(expected), std::end(expected),
      std::begin(measured), std::end(measured)
    );
  }
  //Exit
  {
    assert(g.GetMaze().Get(1, 1) == MazeSquare::exit);
    const auto measured = g.GetSprites(1, 1);
    const auto expected = { Sprite::exit };
    BOOST_CHECK_EQUAL_COLLECTIONS(
      std::begin(expected), std::end(expected),
      std::begin(measured), std::end(measured)
    );
  }
  //Prisoner 1
  {
    const int enemy_frame{0};
    const int prisoner_frame{0};
    const auto measured = g.GetSprites(13, 3, enemy_frame, prisoner_frame);
    const auto expected = { Sprite::prisoner1 };
    BOOST_CHECK_EQUAL_COLLECTIONS(
      std::begin(expected), std::end(expected),
      std::begin(measured), std::end(measured)
    );
  }
  //Prisoner 2
  {
    const int enemy_frame{0};
    const int prisoner_frame{1};
    const auto measured = g.GetSprites(13, 3, enemy_frame, prisoner_frame);
    const auto expected = { Sprite::prisoner2 };
    BOOST_CHECK_EQUAL_COLLECTIONS(
      std::begin(expected), std::end(expected),
      std::begin(measured), std::end(measured)
    );
  }
  //Enemy 1
  {
    const int enemy_frame{0};
    const int prisoner_frame{0};
    const auto measured = g.GetSprites(1, 3, enemy_frame, prisoner_frame);
    const auto expected = { Sprite::enemy1 };
    BOOST_CHECK_EQUAL_COLLECTIONS(
      std::begin(expected), std::end(expected),
      std::begin(measured), std::end(measured)
    );
  }
  //Enemy 2
  {
    const int enemy_frame{1};
    const int prisoner_frame{0};
    const auto measured = g.GetSprites(1, 3, enemy_frame, prisoner_frame);
    const auto expected = { Sprite::enemy2 };
    BOOST_CHECK_EQUAL_COLLECTIONS(
      std::begin(expected), std::end(expected),
      std::begin(measured), std::end(measured)
    );
  }


  //std::copy(std::begin(measured), std::end(measured),
  // std::ostream_iterator<Sprite>(std::cerr, ", "));
}

BOOST_AUTO_TEST_CASE(maziak_game_can_get_sprites_path_visible)
{
/*
    0123456789012345678

 0  XXXXXXXXXXXXXXXXXXX
 1  X!  X X+X.      X X
 2  XXX X X XXX XXXXX X
 3  XZX X X XZ  X:X X X
 4  X X X X XXX X X X X
 5  X   X X         X X
 6  X XXX XXX XXXXXXX X
 7  X                 X
 8  X X XXXXX XXX XXXXX
 9  X X X X X  +X     X
10  X XXX XXX XXX XXXXX
11  X X         X     X
12  X X X X XXX XXXXX X
13  X X+X X+X    ZX   X
14  XXXXXXXXXXXXXXXXXXX

*/
  Game g{CreateTestGame1()};
  g.SetDoShowSolution(true);
  //std::cerr << '\n' << g << '\n';
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
  //Road, not solution
  {
    const auto measured = g.GetSprites(5, 1);
    const auto expected = { Sprite::empty };
    BOOST_CHECK_EQUAL_COLLECTIONS(
      std::begin(expected), std::end(expected),
      std::begin(measured), std::end(measured)
    );
  }
  //Road, solution
  {
    const auto measured = g.GetSprites(2, 1);
    const auto expected = { Sprite::path };
    BOOST_CHECK_EQUAL_COLLECTIONS(
      std::begin(expected), std::end(expected),
      std::begin(measured), std::end(measured)
    );
  }
  //Sword
  {
    const auto measured = g.GetSprites(7, 1);
    const auto expected = { Sprite::sword };
    BOOST_CHECK_EQUAL_COLLECTIONS(
      std::begin(expected), std::end(expected),
      std::begin(measured), std::end(measured)
    );
  }
  //Start should not be visible, but solution should be shown, would not
  //the player stand on it
  {
    assert(g.GetMaze().Get(9, 1) == MazeSquare::start);
    const auto measured = g.GetSprites(9, 1);
    const auto expected = { Sprite::player_look_down_sword };
    BOOST_CHECK_EQUAL_COLLECTIONS(
      std::begin(expected), std::end(expected),
      std::begin(measured), std::end(measured)
    );
  }
  //Exit
  {
    assert(g.GetMaze().Get(1, 1) == MazeSquare::exit);
    const auto measured = g.GetSprites(1, 1);
    const auto expected = { Sprite::exit };
    BOOST_CHECK_EQUAL_COLLECTIONS(
      std::begin(expected), std::end(expected),
      std::begin(measured), std::end(measured)
    );
  }
  //Prisoner 1
  {
    const int enemy_frame{0};
    const int prisoner_frame{0};
    const auto measured = g.GetSprites(13, 3, enemy_frame, prisoner_frame);
    const auto expected = { Sprite::prisoner1 };
    BOOST_CHECK_EQUAL_COLLECTIONS(
      std::begin(expected), std::end(expected),
      std::begin(measured), std::end(measured)
    );
  }
  //Prisoner 2
  {
    const int enemy_frame{0};
    const int prisoner_frame{1};
    const auto measured = g.GetSprites(13, 3, enemy_frame, prisoner_frame);
    const auto expected = { Sprite::prisoner2 };
    BOOST_CHECK_EQUAL_COLLECTIONS(
      std::begin(expected), std::end(expected),
      std::begin(measured), std::end(measured)
    );
  }
  //Enemy 1
  {
    const int enemy_frame{0};
    const int prisoner_frame{0};
    const auto measured = g.GetSprites(1, 3, enemy_frame, prisoner_frame);
    const auto expected = { Sprite::enemy1 };
    BOOST_CHECK_EQUAL_COLLECTIONS(
      std::begin(expected), std::end(expected),
      std::begin(measured), std::end(measured)
    );
  }
  //Enemy 2
  {
    const int enemy_frame{1};
    const int prisoner_frame{0};
    const auto measured = g.GetSprites(1, 3, enemy_frame, prisoner_frame);
    const auto expected = { Sprite::enemy2 };
    BOOST_CHECK_EQUAL_COLLECTIONS(
      std::begin(expected), std::end(expected),
      std::begin(measured), std::end(measured)
    );
  }


  //std::copy(std::begin(measured), std::end(measured),
  // std::ostream_iterator<Sprite>(std::cerr, ", "));
}
