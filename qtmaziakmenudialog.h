#ifndef QTMAZIAKMENUDIALOG2_H
#define QTMAZIAKMENUDIALOG2_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qthideandshowdialog.h"
#include "maziakdifficulty.h"
#pragma GCC diagnostic pop

struct QKeyPressEvent;
struct QMouseEvent;
struct QPaintEvent;

namespace Ui {
  class QtMaziakMenuDialog;
}

namespace ribi {
namespace maziak {

class QtMaziakMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT //!OCLINT

public:
  explicit QtMaziakMenuDialog(QWidget *parent = 0);
  QtMaziakMenuDialog(const QtMaziakMenuDialog&) = delete;
  QtMaziakMenuDialog& operator=(const QtMaziakMenuDialog&) = delete;
  ~QtMaziakMenuDialog() noexcept;

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
