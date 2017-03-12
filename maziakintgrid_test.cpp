#include "maziakintgrid.h"

#include <boost/test/unit_test.hpp>

#include "maziakhelper.h"

using namespace ribi::maziak;

BOOST_AUTO_TEST_CASE(maziak_CreateIntGrid)
{
  const auto sz = 11;
  const auto m = CreateIntGrid(sz);
  BOOST_CHECK(IsSquare(m));
  BOOST_CHECK_EQUAL(GetSize(m), sz);
}

BOOST_AUTO_TEST_CASE(maziak_IsValidSize)
{
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