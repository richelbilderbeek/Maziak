#ifndef QTMAZIAKGAMEOVERDIALOG_H
#define QTMAZIAKGAMEOVERDIALOG_H

#include <QDialog>

class QTimer;

namespace Ui {
  class QtMaziakGameOverDialog;
}

namespace ribi {
namespace maziak {

class QtGameOverDialog : public QDialog
{
  Q_OBJECT //!OCLINT

public:
  explicit QtGameOverDialog(QWidget *parent = 0);
  QtGameOverDialog(const QtGameOverDialog&) = delete;
  QtGameOverDialog& operator=(const QtGameOverDialog&) = delete;
  ~QtGameOverDialog() noexcept;

protected:
  void mousePressEvent(QMouseEvent*);
  void keyPressEvent(QKeyEvent*);
  void showEvent(QShowEvent *);

private:
  Ui::QtMaziakGameOverDialog *ui;
  QTimer * const m_timer; //Owned by this class
  bool m_allow_close;

  private slots:
  void onTimer();

};

} //~namespace maziak
} //~namespace ribi

#endif // QTMAZIAKGAMEOVERDIALOG_H
