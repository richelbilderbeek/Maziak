#include "maziakgamestate.h"

#include <sstream>
#include <boost/test/unit_test.hpp>

using namespace ribi::maziak;

BOOST_AUTO_TEST_CASE(maziak_game_state_to_str)
{
  for (const auto i: get_all_game_states())
  {
    BOOST_CHECK(!to_str(i).empty());
  }
}

BOOST_AUTO_TEST_CASE(maziak_game_state_to_stream)
{
  for (const auto i: get_all_game_states())
  {
    std::stringstream s;
    s << i;
    BOOST_CHECK(!s.str().empty());
  }
}

