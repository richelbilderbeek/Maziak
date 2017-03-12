#ifndef QTMAZIAKSPRITES_TEST_H
#define QTMAZIAKSPRITES_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace maziak {

class QtSprites_test : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void images_are_correct();
};

} //~namespace maziak
} //~namespace ribi

#endif // QTMAZIAKSPRITES_TEST_H
