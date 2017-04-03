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


//class QtDisplay : public QWidget
class QtDisplay : public QDialog
{
  Q_OBJECT //!OCLINT

public:

  typedef unsigned int WORD;

  explicit QtDisplay(QWidget *parent = 0);
  QtDisplay(const QtDisplay&) = delete;
  QtDisplay& operator=(const QtDisplay&) = delete;
  ~QtDisplay() {}

  ///Show the main dialog's state
  //void DoDisplay(const MainDialog& main_dialog);

  const auto& GetSprites() const noexcept { return m_sprites; }

  ///The heigh of the view displayed, in number of blocks
  int GetViewHeight() const noexcept { return 9; }

  ///The width of the view displayed, in number of blocks
  int GetViewWidth() const noexcept { return 9; }

  bool MustAnimateEnemiesAndPrisoners() noexcept;

  std::set<Key> RequestKeys();

private:

  ///The game logic
  Game m_game;

  //Will be painted
  QImage m_image;

  std::set<Key> m_keys;

  const Sprites m_sprites;
  Stopwatch m_timer_animate_enemies_and_prisoners;
  Stopwatch m_timer_show_solution;


  //void DisplaySpritesFloor();
  //void DisplaySpritesAboveFloor();
  //void DisplayPlayer();


  bool GetDoShowSolution();

  void OnGameOver();
  void OnGameWon();
  void OnTimerStartShowingSolution();
  void Paint(QPainter& painter, const QRect& target);
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
