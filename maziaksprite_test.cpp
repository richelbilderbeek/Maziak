#include "maziaksprite.h"

#include <sstream>
#include <boost/test/unit_test.hpp>

using namespace ribi::maziak;

BOOST_AUTO_TEST_CASE(maziak_sprite_to_char)
{
  for (const auto i: get_all_sprites())
  {
    BOOST_CHECK_NO_THROW(to_char(i));
  }
}

BOOST_AUTO_TEST_CASE(maziak_sprite_to_str)
{
  for (const auto i: get_all_sprites())
  {
    BOOST_CHECK(!to_str(i).empty());
  }
}

BOOST_AUTO_TEST_CASE(maziak_sprite_to_stream)
{
  for (const auto i: get_all_sprites())
  {
    std::stringstream s;
    s << i;
    BOOST_CHECK(!s.str().empty());
  }
}



