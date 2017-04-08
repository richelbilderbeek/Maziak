#include "maziakintgrid.h"

#include <boost/test/unit_test.hpp>

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
