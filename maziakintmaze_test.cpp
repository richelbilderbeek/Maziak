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

BOOST_AUTO_TEST_CASE(maziak_CreateIntMaze)
{
  const auto sz = 11;
  const auto m = CreateIntMaze(sz);
  BOOST_CHECK(IsSquare(m));
  BOOST_CHECK_EQUAL(GetSize(m), sz);
}

BOOST_AUTO_TEST_CASE(maziak_CreateIntMaze_abuse)
{
  BOOST_CHECK_NO_THROW(CreateIntMaze( 7));
  BOOST_CHECK_NO_THROW(CreateIntMaze(11));
  BOOST_CHECK_THROW(CreateIntMaze(6), std::exception);
  BOOST_CHECK_THROW(CreateIntMaze(8), std::exception);
}

#pragma GCC diagnostic pop
