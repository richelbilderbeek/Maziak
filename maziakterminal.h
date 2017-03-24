#ifndef MAZIAKTERMINAL_H
#define MAZIAKTERMINAL_H

//#include "maziakdisplay.h"

#include "maziakgame.h"

namespace ribi {
namespace maziak {

///Displays Game in command-line mode
/// Does all the game dynamic:
///  * Animate the enemies and prisoners: toggle the two displays of enemies
///  * Animate fighting: if there is a fight, go to the next fighting frame
struct Terminal
{
  Terminal(const Game& game);

  ///Start the game in a terminal, until the game is over or quit
  void Execute();

  bool GetDoShowSolution() { --m_do_show_solution_cnt; return m_do_show_solution_cnt > 0; }

  const Game& GetGame() const noexcept { return m_game; }

  /// 0: first animation frame, 1: second animation frame
  int GetPrisonerFrame() const noexcept { return m_prisoner_frame; }

  ///The heigh of the view displayed, in number of blocks
  int GetViewHeight() const noexcept { return 20; }

  ///The width of the view displayed, in number of blocks
  int GetViewWidth() const noexcept { return 20; }

  ///Every turn, the animation must take place
  bool MustAnimateEnemiesAndPrisoners() noexcept { return true; }

  std::set<Key> RequestKeys();

  void StartShowSolution() { m_do_show_solution_cnt = 20; }

  ///Toggles the prisoner animation
  void TogglePrisoners() { m_prisoner_frame = (m_prisoner_frame + 1) % 2;  }

  private:
  int m_do_show_solution_cnt;

  ///The game logic
  Game m_game;

  /// 0: first animation frame, 1: second animation frame
  int m_prisoner_frame;
};

Terminal CreateTestTerminal1();

std::string to_str(const Terminal& t);

std::ostream& operator<<(std::ostream& os, const Terminal& t);

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKTERMINAL_H
