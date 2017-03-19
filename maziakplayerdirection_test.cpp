#include "maziakplayerdirection.h"

#include <sstream>
#include <boost/test/unit_test.hpp>

using namespace ribi::maziak;

BOOST_AUTO_TEST_CASE(maziak_player_direction_to_str)
{
  for (const auto i: get_all_player_directions())
  {
    BOOST_CHECK(!to_str(i).empty());
  }
}

BOOST_AUTO_TEST_CASE(maziak_player_direction_to_stream)
{
  for (const auto i: get_all_player_directions())
  {
    std::stringstream s;
    s << i;
    BOOST_CHECK(!s.str().empty());
  }
}



