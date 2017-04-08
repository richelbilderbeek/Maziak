#ifndef QTMAZIAKMENUDIALOG2_H
#define QTMAZIAKMENUDIALOG2_H

#include <QDialog>
#include "maziakdifficulty.h"

struct QKeyPressEvent;
struct QMouseEvent;
struct QPaintEvent;

namespace Ui {
  class QtMaziakMenuDialog;
}

namespace ribi {
namespace maziak {

class QtMenuDialog : public QDialog
{
  Q_OBJECT //!OCLINT

public:
  explicit QtMenuDialog(QWidget *parent = 0);
  QtMenuDialog(const QtMenuDialog&) = delete;
  QtMenuDialog& operator=(const QtMenuDialog&) = delete;
  ~QtMenuDialog() noexcept;

private:
  Ui::QtMaziakMenuDialog *ui;
  int GetMazeSize() const;
  Difficulty m_difficulty;
  void keyPressEvent(QKeyEvent * event);
  void mousePressEvent(QMouseEvent * event);
  void paintEvent(QPaintEvent*);
  void OnStart();
  void OnInstructions();
  void OnAbout();
};

} //~namespace maziak
} //~namespace ribi

#endif // QTMAZIAKMENUDIALOG2_H
