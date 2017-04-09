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
    const int rng_seed = -1,
    QWidget *parent = 0
  );
  QtMenuDialog(const QtMenuDialog&) = delete;
  QtMenuDialog& operator=(const QtMenuDialog&) = delete;
  ~QtMenuDialog() noexcept;

  auto GetDifficulty() const noexcept { return m_difficulty; }
  auto GetRngSeed() const noexcept { return m_rng_seed; }

  #ifndef NDEBUG
  void DisablePopups() noexcept { m_allow_popups = false; }
  const auto& GetUi() const noexcept { return *ui; }
  #endif // NDEBUG

private:
  Ui::QtMaziakMenuDialog *ui;

  bool m_allow_popups;
  Difficulty m_difficulty;
  const int m_rng_seed;

  int GetMazeSize() const;
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
