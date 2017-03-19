#include "maziakintmaze.h"

// Boost.Test does not play well with -Weffc++
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/test/unit_test.hpp>

using namespace ribi::maziak;

BOOST_AUTO_TEST_CASE(maziak_IntMaze_size)
{
  const auto sz = 11;
  const IntMaze m(sz);
  BOOST_CHECK(IsSquare(m));
  BOOST_CHECK_EQUAL(GetSize(m), sz);
}

BOOST_AUTO_TEST_CASE(maziak_IntMaze_CanGet)
{
  const auto sz = 11;
  const int rng_seed{42};
  const auto m = CreateIntMaze(sz, rng_seed);
  BOOST_CHECK( m.CanGet(0,0));
  BOOST_CHECK( m.CanGet(10,10));
  BOOST_CHECK(!m.CanGet( 0,11));
  BOOST_CHECK(!m.CanGet(11, 0));
  BOOST_CHECK(!m.CanGet(-1, 0));
  BOOST_CHECK(!m.CanGet( 0,-1));
}

BOOST_AUTO_TEST_CASE(maziak_CreateIntMaze)
{
  const auto sz = 11;
  const int rng_seed{42};
  const auto m = CreateIntMaze(sz, rng_seed);
  BOOST_CHECK(IsSquare(m));
  BOOST_CHECK_EQUAL(GetSize(m), sz);
}


BOOST_AUTO_TEST_CASE(maziak_CreateIntMaze_abuse)
{
  const int rng_seed{42};
  BOOST_CHECK_NO_THROW(CreateIntMaze( 7, rng_seed));
  BOOST_CHECK_NO_THROW(CreateIntMaze(11, rng_seed));
  BOOST_CHECK_THROW(CreateIntMaze(6, rng_seed), std::exception);
  BOOST_CHECK_THROW(CreateIntMaze(8, rng_seed), std::exception);
}

#pragma GCC diagnostic pop

