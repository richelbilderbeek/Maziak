#include "maziakintmaze.h"

#include <iostream>
#include <boost/timer/timer.hpp>
#include <boost/test/unit_test.hpp>

using namespace ribi::maziak;

BOOST_AUTO_TEST_CASE(maziak_IntMaze_size)
{
  const auto sz = 11;
  const auto rng_seed = 42;
  const IntMaze m(sz, sz, rng_seed);
  BOOST_CHECK_EQUAL(get_n_cols(m), sz);
  BOOST_CHECK_EQUAL(get_n_rows(m), sz);
}

BOOST_AUTO_TEST_CASE(maziak_IntMaze_CanGet)
{
  const auto sz = 11;
  const int rng_seed{42};
  const auto m = CreateIntMaze(sz, sz, rng_seed);
  BOOST_CHECK( m.CanGet(Coordinat( 0, 0)));
  BOOST_CHECK( m.CanGet(Coordinat(10,10)));
  BOOST_CHECK(!m.CanGet(Coordinat( 0,11)));
  BOOST_CHECK(!m.CanGet(Coordinat(11, 0)));
  BOOST_CHECK(!m.CanGet(Coordinat(-1, 0)));
  BOOST_CHECK(!m.CanGet(Coordinat( 0,-1)));
}

BOOST_AUTO_TEST_CASE(maziak_CreateIntMaze)
{
  const auto sz = 11;
  const int rng_seed{42};
  const auto m = CreateIntMaze(sz, sz, rng_seed);
  BOOST_CHECK_EQUAL(get_n_cols(m), sz);
  BOOST_CHECK_EQUAL(get_n_rows(m), sz);
}


BOOST_AUTO_TEST_CASE(maziak_CreateIntMaze_abuse)
{
  const int rng_seed{42};
  BOOST_CHECK_NO_THROW(CreateIntMaze( 7, 7, rng_seed));
  BOOST_CHECK_NO_THROW(CreateIntMaze(11, 11, rng_seed));
  BOOST_CHECK_THROW(CreateIntMaze(6, 6, rng_seed), std::exception);
  BOOST_CHECK_THROW(CreateIntMaze(8, 6, rng_seed), std::exception);
}

BOOST_AUTO_TEST_CASE(maziak_CreateIntMaze_can_be_rectangular)
{
  const int rng_seed{42};
  BOOST_CHECK_NO_THROW(CreateIntMaze( 7, 7, rng_seed));
  BOOST_CHECK_NO_THROW(CreateIntMaze(11, 11, rng_seed));
  BOOST_CHECK_NO_THROW(CreateIntMaze( 7, 11, rng_seed));
}

BOOST_AUTO_TEST_CASE(maziak_CreateIntMaze_must_reproduce_same_maze_each_time)
{
  const auto sz = 15;
  const int rng_seed{145};
  const IntMaze m{CreateIntMaze(sz, sz, rng_seed)};
  const IntMaze n{CreateIntMaze(sz, sz, rng_seed)};
  BOOST_CHECK_EQUAL(m, n);
}

BOOST_AUTO_TEST_CASE(maziak_CollectDeadEnds)
{
  const auto sz = 7;
  const int rng_seed{145};
  const IntMaze m{CreateIntMaze(sz, sz, rng_seed)};
  BOOST_CHECK(!CollectDeadEnds(m).empty());
}

BOOST_AUTO_TEST_CASE(maziak_CollectDeadEndsImpls_give_same_result)
{
  const auto sz = 7;
  static_assert(IsValidSize(sz), "");
  const int rng_seed{145};
  const IntMaze m{CreateIntMaze(sz, sz, rng_seed)};
  const auto v = CollectDeadEndsImpl1(m.Get());
  const auto w = CollectDeadEndsImpl2(m.Get());
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(maziak_CollectDeadEndsImpls_speed)
{
  const auto sz = 107;
  static_assert(IsValidSize(sz), "");
  const int rng_seed{145};
  const IntMaze m{CreateIntMaze(sz, sz, rng_seed)};

  double t1_sec{0.0};
  {
    boost::timer::cpu_timer timer;
    CollectDeadEndsImpl1(m.Get());
    t1_sec = static_cast<double>(timer.elapsed().user) / 1'000'000'000.0;
  }
  double t2_sec{0.0};
  {
    boost::timer::cpu_timer timer;
    CollectDeadEndsImpl2(m.Get());
    t2_sec = static_cast<double>(timer.elapsed().user) / 1'000'000'000.0;
  }
  std::clog << "CollectDeadEndsImpls: " << t1_sec << " and " << t2_sec << " (sec)\n";
  BOOST_CHECK(t2_sec < 0.5 * t1_sec);
}
