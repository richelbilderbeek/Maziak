#include "maziakhelper.h"

#include <boost/test/unit_test.hpp>

using namespace ribi::maziak;

BOOST_AUTO_TEST_CASE(maziak_IsSquare)
{
  //Empty should throw
  {
    const std::vector<std::vector<int>> v;
    BOOST_CHECK_THROW(IsSquare(v), std::exception);
  }
  //1x1
  {
    const std::vector<std::vector<int>> v(1, std::vector<int>(1));
    BOOST_CHECK(IsSquare(v));
  }
  //2x2
  {
    const std::vector<std::vector<int>> v(2, std::vector<int>(2));
    BOOST_CHECK(IsSquare(v));
  }
  //2x1
  {
    const std::vector<std::vector<int>> v(2, std::vector<int>(1));
    BOOST_CHECK(!IsSquare(v));
  }
  //1x2
  {
    const std::vector<std::vector<int>> v(1, std::vector<int>(2));
    BOOST_CHECK(!IsSquare(v));
  }
  //Jagged
  {
    const std::vector<std::vector<int>> v =
    {
      {1,2},
      {1}
    };
    BOOST_CHECK(!IsSquare(v));
  }
}

BOOST_AUTO_TEST_CASE(maziak_CamelCasify)
{
  BOOST_CHECK_EQUAL(CamelCasify("player_look_down_sword"), "playerLookDownSword");
}
