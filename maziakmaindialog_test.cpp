#include "maziakmaindialog.h"

#include <boost/test/unit_test.hpp>

using namespace ribi::maziak;

BOOST_AUTO_TEST_CASE(maziak_MainDialog_construction)
{
  const int rng_seed{234};
  const MainDialog d{7 + (4 * 2), rng_seed};
  BOOST_CHECK(!d.GetDoShowSolution());
}

BOOST_AUTO_TEST_CASE(maziak_MainDialog_stream_out)
{
  const int rng_seed{234};
  const MainDialog d{7 + (4 * 2), rng_seed};
  std::stringstream s;
  s << d;
  BOOST_CHECK(!s.str().empty());
}
