#include "maziakmaindialog.h"

#include <boost/test/unit_test.hpp>

using namespace ribi::maziak;

BOOST_AUTO_TEST_CASE(maziak_MainDialog_construction)
{
  const MainDialog d{CreateTestMaze1()};
  BOOST_CHECK(!d.GetDoShowSolution());
}

BOOST_AUTO_TEST_CASE(maziak_MainDialog_stream_out)
{
  const MainDialog d{CreateTestMaze1()};
  std::stringstream s;
  s << d;
  BOOST_CHECK(!s.str().empty());
}

BOOST_AUTO_TEST_CASE(maziak_CreateTestMainDialog1)
{
  const auto d = CreateTestMainDialog1();
  const auto m1 = d.GetMaze().Get();
  const auto m2 = CreateTestMaze1().Get();
  BOOST_CHECK_EQUAL(m1, m2);
}

