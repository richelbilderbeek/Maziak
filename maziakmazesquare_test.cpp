#include "maziakmazesquare.h"

#include <sstream>
#include <boost/test/unit_test.hpp>

using namespace ribi::maziak;

BOOST_AUTO_TEST_CASE(maziak_maze_square_to_char)
{
  for (const auto i: get_all_maze_squares())
  {
    BOOST_CHECK_NO_THROW(to_char(i));
  }
}

BOOST_AUTO_TEST_CASE(maziak_maze_square_to_str)
{
  for (const auto i: get_all_maze_squares())
  {
    BOOST_CHECK(!to_str(i).empty());
  }
}

BOOST_AUTO_TEST_CASE(maziak_maze_square_to_stream)
{
  for (const auto i: get_all_maze_squares())
  {
    std::stringstream s;
    s << i;
    BOOST_CHECK(!s.str().empty());
  }
}


