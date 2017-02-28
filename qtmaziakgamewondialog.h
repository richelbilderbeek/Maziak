#ifndef QTMAZIAKGAMEWONDIALOG_H
#define QTMAZIAKGAMEWONDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

struct QTimer;

namespace Ui {
  class QtMaziakGameWonDialog;
}

namespace ribi {

class QtMaziakGameWonDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtMaziakGameWonDialog(QWidget *parent = 0);
  QtMaziakGameWonDialog(const QtMaziakGameWonDialog&) = delete;
  QtMaziakGameWonDialog& operator=(const QtMaziakGameWonDialog&) = delete;
  ~QtMaziakGameWonDialog() noexcept;

protected:
  void paintEvent(QPaintEvent*);
  void mousePressEvent(QMouseEvent*);
  void keyPressEvent(QKeyEvent*);

private:
  Ui::QtMaziakGameWonDialog *ui;
  boost::shared_ptr<QTimer> m_timer;
  bool m_allow_close;

  private slots:
  void onTimer();
};

} //~namespace ribi

#endif // QTMAZIAKGAMEWONDIALOG_H
