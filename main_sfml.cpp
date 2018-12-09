#include <gsl/gsl_assert>
#include <memory>
#include "maziakintgrid.h"
#include "maziakmenudialog.h"

int main(int, char *[])
{
  #ifdef NDEBUG
  //Must be really release mode
  assert(1 == 2);
  //Not now, see https://github.com/richelbilderbeek/travis_qmake_gcc_cpp14_debug_and_release_gsl/issues/1
  //Expects(1 == 2);
  //Ensures(1 == 2);
  #endif
  using namespace ribi::maziak;
  //ribi::maziak::SfmlGameDialog w;
  //w.exec();
}

