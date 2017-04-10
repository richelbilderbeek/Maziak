#include <QApplication>
#include <QTimer>
#include <gsl/gsl_assert>
#include <memory>
#include "qtmaziakmenudialog.h"

#include "qtmaziakinstructionsdialog.h"
#include "qtaboutdialog.h"
#include "maziakintgrid.h"
#include "maziakmenudialog.h"
#include "qtmaziakdisplay.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  #ifdef NDEBUG
  //Must be really release mode
  assert(1 == 2);
  //Not now, see https://github.com/richelbilderbeek/travis_qmake_gcc_cpp14_debug_and_release_gsl/issues/1
  //Expects(1 == 2);
  //Ensures(1 == 2);
  #endif
  using namespace ribi::maziak;
  if (argc == 2 && std::string(argv[1]) == "--profile")
  {
    const int maze_sz{999};
    static_assert(IsValidSize(maze_sz), "");
    QtDisplay d(maze_sz, maze_sz, 42, 31, 31);
    QTimer::singleShot(10000, &d, SLOT(close()));
    d.showFullScreen();
    d.exec();
    a.exit(0);
  }
  else
  {
    const int no_rng_seed{-1};
    ribi::maziak::QtMenuDialog w(no_rng_seed);
    w.show();
    return a.exec();
  }
}

