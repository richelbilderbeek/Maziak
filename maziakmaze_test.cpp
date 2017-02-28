#include "maziakmaze.h"

// Boost.Test does not play well with -Weffc++
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/test/unit_test.hpp>

using namespace maziak;

BOOST_AUTO_TEST_CASE(maze_constructor)
{
  BOOST_CHECK_NO_THROW(Maze(11));
}

#pragma GCC diagnostic pop

