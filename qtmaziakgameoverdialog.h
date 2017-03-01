#ifndef QTMAZIAKGAMEOVERDIALOG_H
#define QTMAZIAKGAMEOVERDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

struct QTimer;

namespace Ui {
  class QtMaziakGameOverDialog;
}

namespace ribi {

class QtMaziakGameOverDialog : public QtHideAndShowDialog
{
  Q_OBJECT //!OCLINT

public:
  explicit QtMaziakGameOverDialog(QWidget *parent = 0);
  QtMaziakGameOverDialog(const QtMaziakGameOverDialog&) = delete;
  QtMaziakGameOverDialog& operator=(const QtMaziakGameOverDialog&) = delete;
  ~QtMaziakGameOverDialog() noexcept;

protected:
  void paintEvent(QPaintEvent*);
  void mousePressEvent(QMouseEvent*);
  void keyPressEvent(QKeyEvent*);

private:
  Ui::QtMaziakGameOverDialog *ui;
  boost::shared_ptr<QTimer> m_timer;
  bool m_allow_close;

  private slots:
  void onTimer();

};

} //~namespace ribi

#endif // QTMAZIAKGAMEOVERDIALOG_H
