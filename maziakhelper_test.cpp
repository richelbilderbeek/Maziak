#include "maziakhelper.h"

#include <boost/test/unit_test.hpp>

using namespace ribi::maziak;

BOOST_AUTO_TEST_CASE(maziak_CamelCasify)
{
  BOOST_CHECK_EQUAL(CamelCasify("player_look_down_sword"), "playerLookDownSword");
}
