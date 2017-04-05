#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QApplication>
#include <QTimer>
#include <gsl/gsl_assert>
#include <memory>
#include "qtmaziakmenudialog.h"

#include "qtmaziakinstructionsdialog.h"
#include "qtaboutdialog.h"
#include "maziakmenudialog.h"
#include "qtmaziakdisplay.h"
#pragma GCC diagnostic pop

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

  if (argc == 2 && std::string(argv[1]) == "--profile")
  {
    ribi::maziak::QtDisplay d(31, 31);
    QTimer::singleShot(10000, &d, SLOT(close()));
    d.showFullScreen();
    d.exec();
    a.exit(0);
  }
  else
  {
    ribi::maziak::QtMaziakMenuDialog w;
    w.show();
    return a.exec();
  }
}

