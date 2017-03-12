#ifndef MAZIAKDISPLAY_H
#define MAZIAKDISPLAY_H

#include <set>

#include "maziakgamestate.h"
#include "maziakkey.h"

namespace ribi {
namespace maziak {

struct MainDialog;

/*
enum class DisplayType { terminal, qt };

///The heigh of the view displayed, in number of blocks
template <DisplayType>
constexpr int GetViewHeight();

template <>
constexpr int GetViewHeight<DisplayType::terminal>() { return 20; }

template <>
constexpr int GetViewHeight<DisplayType::qt>() { return 9; }

///The width of the view displayed, in number of blocks
template <DisplayType>
constexpr int GetViewWidth();

template <>
constexpr int GetViewWidth<DisplayType::terminal>() { return 20; }

template <>
constexpr int GetViewWidth<DisplayType::qt>() { return 9; }
*/

///Displays Maziak in any way
///Cannot use Boost or Qt due to NDS library
struct Display
{
  Display();

  virtual ~Display() {}

  //Put the MainDialog on screen, where the screen may be a terminal, QWidget or NDS screen
  virtual void DoDisplay(const MainDialog& main_dialog) = 0;

  ///Still showing the solution? Can be no after a certain amount
  ///of ticks or seconds after StartShowSolution
  virtual bool GetDoShowSolution() = 0;

  GameState GetGameState() const noexcept { return m_game_state; }

  ///The heigh of the view displayed, in number of blocks
  virtual int GetViewHeight() const noexcept = 0;

  ///The width of the view displayed, in number of blocks
  virtual int GetViewWidth() const noexcept = 0;

  ///Must the enemies and prisoners be animated?
  ///In a terminal version: every turn
  ///In a graphical version: every so many seconds
  virtual bool MustAnimateEnemiesAndPrisoners() noexcept = 0;

  virtual std::set<Key> RequestKeys() = 0;

  void SetGameState(const GameState game_state) noexcept { m_game_state = game_state; }

  ///Make a clock or other mechanism start
  virtual void StartShowSolution() = 0;

  private:
  GameState m_game_state;
};

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKDISPLAY_H
