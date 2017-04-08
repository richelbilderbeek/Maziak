#ifndef QTMAZIAKINSTRUCTIONSDIALOG_TEST_H
#define QTMAZIAKINSTRUCTIONSDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace maziak {

class QtInstructionsDialog_test : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void display();
};

} //~namespace maziak
} //~namespace ribi

#endif // QTMAZIAKINSTRUCTIONSDIALOG_TEST_H
