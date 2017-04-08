#ifndef QTMAZIAKGAMEWONDIALOG_H
#define QTMAZIAKGAMEWONDIALOG_H

#include <QDialog>

struct QTimer;

namespace Ui {
  class QtMaziakGameWonDialog;
}

namespace ribi {
namespace maziak {

class QtGameWonDialog : public QDialog
{
  Q_OBJECT //!OCLINT

public:
  explicit QtGameWonDialog(QWidget *parent = 0);
  QtGameWonDialog(const QtGameWonDialog&) = delete;
  QtGameWonDialog& operator=(const QtGameWonDialog&) = delete;
  ~QtGameWonDialog() noexcept;

protected:
  void paintEvent(QPaintEvent*);
  void mousePressEvent(QMouseEvent*);
  void keyPressEvent(QKeyEvent*);

private:
  Ui::QtMaziakGameWonDialog *ui;
  QTimer * const m_timer; //Owned by this dialog
  bool m_allow_close;

  private slots:
  void onTimer();
};

} //~namespace maziak
} //~namespace ribi

#endif // QTMAZIAKGAMEWONDIALOG_H
