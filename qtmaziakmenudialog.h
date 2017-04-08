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
  /// @param rng_seed Random number generator seed. Use a negative value for
  ///   a random seed, use a positive value to set the seed
  explicit QtMenuDialog(
    const int rng_seed,
    QWidget *parent = 0
  );
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

  const int m_rng_seed;
};

} //~namespace maziak
} //~namespace ribi

#endif // QTMAZIAKMENUDIALOG2_H
