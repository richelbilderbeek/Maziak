#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtmaziakdisplay.h"

#include <algorithm>
#include <cassert>
#include <cmath>

#include <iostream>
#include <stdexcept>
#include <vector>

#include <boost/scoped_ptr.hpp>

#include <QDesktopWidget>
#include <QApplication>
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include "maziakhelper.h"
#include "maziakintmaze.h"
#include "maziakmaze.h"
#include "maziaksprites.h"
#include "qtmaziakgameoverdialog.h"
#include "testtimer.h"
#include "qtmaziakgamewondialog.h"
#include "qtgraphics.h"
#include "maziaksolutionmaze.h"
#include "maziakmaindialog.h"
#include "trace.h"

#pragma GCC diagnostic pop

void ribi::TestQtDisplay() noexcept
{
  {
    QtDisplay q;
    //Cannot test this in constructor: never call virtual functions in a class constructor
    assert(q.GetViewHeight() == 9);
    assert(q.GetViewWidth() == 9);
  }
  {
    QtDisplay q;
    maziak::MainDialog d(7);
    d.SetDisplay(&q);
    q.show();
  }
}
