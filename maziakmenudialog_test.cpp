#include "maziakmenudialog.h"

#include <sstream>
#include <boost/test/unit_test.hpp>

using namespace ribi::maziak;

BOOST_AUTO_TEST_CASE(maziak_menu_dialog_get_info)
{
  MenuDialog d;
  BOOST_CHECK_NO_THROW(d.GetAbout());
  BOOST_CHECK_NO_THROW(d.GetHelp());
  BOOST_CHECK_NO_THROW(d.GetVersion());
  BOOST_CHECK_NO_THROW(d.GetVersionHistory());
}
