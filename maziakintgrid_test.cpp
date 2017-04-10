#include "maziakintgrid.h"

#include <iostream>
#include <boost/test/unit_test.hpp>
#include <boost/timer/timer.hpp>

#include "maziakhelper.h"

using namespace ribi::maziak;

BOOST_AUTO_TEST_CASE(maziak_CreateIntGrid)
{
  const auto sz = 15;
  const int rng_seed{145};
  const auto m = CreateIntGrid(sz, sz, rng_seed);
  BOOST_CHECK_EQUAL(get_n_cols(m), sz);
  BOOST_CHECK_EQUAL(get_n_rows(m), sz);
}

BOOST_AUTO_TEST_CASE(maziak_IsValidSize)
{
  static_assert(!IsValidSize(-1), "");
  static_assert(!IsValidSize( 0), "");
  static_assert(!IsValidSize( 1), "");
  static_assert(!IsValidSize( 2), "");
  static_assert(!IsValidSize( 3), "");
  static_assert(!IsValidSize( 4), "");
  static_assert(!IsValidSize( 5), "");
  static_assert(!IsValidSize( 6), "");
  static_assert( IsValidSize( 7), "");
  static_assert( IsValidSize(11), "");
  static_assert( IsValidSize(15), "");

  BOOST_CHECK(!IsValidSize(-1));
  BOOST_CHECK(!IsValidSize( 0));
  BOOST_CHECK(!IsValidSize( 1));
  BOOST_CHECK(!IsValidSize( 2));
  BOOST_CHECK(!IsValidSize( 3));
  BOOST_CHECK(!IsValidSize( 4));
  BOOST_CHECK(!IsValidSize( 5));
  BOOST_CHECK(!IsValidSize( 6));
  BOOST_CHECK( IsValidSize( 7));
  BOOST_CHECK( IsValidSize(11));
  BOOST_CHECK( IsValidSize(15));
}

BOOST_AUTO_TEST_CASE(maziak_CreateIntGridImpls_speed)
{
  const auto sz = 403;
  static_assert(IsValidSize(sz), "");
  const int rng_seed{145};
  double t1_sec{0.0};
  {
    boost::timer::cpu_timer timer;
    CreateIntGridImpl1(sz, sz, rng_seed);
    t1_sec = static_cast<double>(timer.elapsed().user) / 1'000'000'000.0;
  }
  double t2_sec{0.0};
  {
    boost::timer::cpu_timer timer;
    CreateIntGridImpl2(sz, sz, rng_seed);
    t2_sec = static_cast<double>(timer.elapsed().user) / 1'000'000'000.0;
  }
  //std::clog << "Maze algorithm times: " << t1_sec << " and " << t2_sec << " (sec)\n";
  BOOST_CHECK_CLOSE(t1_sec, t2_sec, 10.0);
}
