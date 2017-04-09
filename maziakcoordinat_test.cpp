#include "maziakcoordinat.h"

#include <iostream>
#include <boost/test/unit_test.hpp>

using namespace ribi::maziak;

BOOST_AUTO_TEST_CASE(maziak_coordinat_construction_curly)
{
  const auto x = 10;
  const auto y = 5;
  const Coordinat c{x, y};
  BOOST_CHECK_EQUAL(get_x(c) , x);
  BOOST_CHECK_EQUAL(get_y(c) , y);
}

BOOST_AUTO_TEST_CASE(maziak_coordinat_construction_round)
{
  const auto x = 8;
  const auto y = 4;
  const Coordinat c(x, y);
  BOOST_CHECK_EQUAL(get_x(c) , x);
  BOOST_CHECK_EQUAL(get_y(c) , y);
}

BOOST_AUTO_TEST_CASE(maziak_get_adjacent_4)
{
  constexpr Coordinat c{10,5};
  const std::vector<Coordinat> measured = get_adjacent_4(c);
  const std::vector<Coordinat> expected = {
    Coordinat{10, 4},
    Coordinat{11, 5},
    Coordinat{10, 6},
    Coordinat{ 9, 5}
  };

  BOOST_CHECK_EQUAL(measured.size(), expected.size());
  BOOST_CHECK(measured[0] == expected[0]);
  BOOST_CHECK(measured[1] == expected[1]);
  BOOST_CHECK(measured[2] == expected[2]);
  BOOST_CHECK(measured[3] == expected[3]);
  /*
  BOOST_CHECK_EQUAL_COLLECTIONS(
    std::begin(measured), std::end(measured),
    std::begin(expected), std::end(expected)
  );
  */
}
