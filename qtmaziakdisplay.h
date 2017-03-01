#ifndef QTMAZIAKDISPLAY_H
#define QTMAZIAKDISPLAY_H

#include <cassert>
#include <map>
#include <set>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#include "maziakmazesquare.h"
#include "maziaksprite.h"
#include "maziakdisplay.h"
#include "maziakfwd.h"
#include "maziakkey.h"
#include "maziaksprites.h"
#include "maziakplayerdirection.h"
#include "maziakplayermove.h"
#include "stopwatch.h"
#pragma GCC diagnostic pop

struct QPixmap;
struct QTimer;

namespace ribi {
namespace maziak {


class QtDisplay : public QWidget, public Display
{
  Q_OBJECT //!OCLINT

public:

  explicit QtDisplay(QWidget *parent = 0);
  QtDisplay(const QtDisplay&) = delete;
  QtDisplay& operator=(const QtDisplay&) = delete;
  ~QtDisplay() {}

  void DoDisplay(const MainDialog& main_dialog) override;

  int GetViewHeight() const noexcept override { return 9; }
  int GetViewWidth() const noexcept override { return 9; }

  bool MustAnimateEnemiesAndPrisoners() noexcept override;

  std::set<Key> RequestKeys() override;

private:
  typedef unsigned int WORD;

  //Will be painted
  QImage m_image;

  std::set<Key> m_keys;

  const Sprites m_sprites;
  Stopwatch m_timer_animate_enemies_and_prisoners;
  Stopwatch m_timer_show_solution;

  static std::map<WORD,Key> CreateDefaultKeys() noexcept;
  bool GetDoShowSolution() override;

  void OnGameOver();
  void OnGameWon();
  void OnTimerStartShowingSolution();
  void StartShowSolution();

  void resizeEvent(QResizeEvent*);
  void keyPressEvent(QKeyEvent * e);
  void keyReleaseEvent(QKeyEvent * e);
  void paintEvent(QPaintEvent * event);
};

} //~namespace maziak
} //~namespace ribi

#endif // QTMAZIAKDISPLAY_H
