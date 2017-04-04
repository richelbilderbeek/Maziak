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
#include "maziakgame.h"
#include "maziakfwd.h"
#include "maziakkey.h"
#include "qtmaziaksprites.h"
#include "maziakplayerdirection.h"
#include "maziakplayermove.h"
#include "stopwatch.h"
#pragma GCC diagnostic pop

struct QPixmap;
struct QTimer;

namespace ribi {
namespace maziak {

///
class QtDisplay : public QDialog
{
  Q_OBJECT //!OCLINT

public:

  typedef unsigned int WORD;

  explicit QtDisplay(
    const int view_height,
    const int view_width,
    QWidget *parent = 0
  );

public slots:

  ///Process the keys and movements. Must result in a speed that can be
  ///followed by a human
  void Respond();

  ///The heartbeat of the game, shows the game state,
  ///must be called 60 times per second
  void Tick();


private:

  ///The game logic
  Game m_game;

  ///The keys that are pressed
  std::set<Key> m_keys;

  const Sprites m_sprites;
  Stopwatch m_timer_animate_enemies_and_prisoners;
  Stopwatch m_timer_show_solution;

  ///The number of blocks the player can view, vertically
  const int m_view_height;

  ///The number of blocks the player can view, horizontally
  const int m_view_width;

  bool GetDoShowSolution();
  int GetEnemiesAndPrisonersFrame() noexcept;

  void OnGameOver();
  void OnGameWon();
  void OnTimerStartShowingSolution();
  void StartShowSolution();

  void resizeEvent(QResizeEvent*);
  void keyPressEvent(QKeyEvent * e);
  void keyReleaseEvent(QKeyEvent * e);
  void paintEvent(QPaintEvent * event);
};

std::map<QtDisplay::WORD,Key> CreateDefaultKeys() noexcept;

} //~namespace maziak
} //~namespace ribi

#endif // QTMAZIAKDISPLAY_H
