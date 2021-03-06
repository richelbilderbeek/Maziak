#ifndef MAZIAKTERMINAL_H
#define MAZIAKTERMINAL_H

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
  [[noreturn]] void Execute();

  bool GetDoShowSolution() { --m_do_show_solution_cnt; return m_do_show_solution_cnt > 0; }

  /// 0: first animation frame, 1: second animation frame
  int GetEnemyFrame() const noexcept { return m_enemy_frame; }

  const auto& GetGame() const noexcept { return m_game; }
  auto& GetGame() noexcept { return m_game; }

  MazeSquare GetPlayerSquare() const noexcept { return m_game.GetPlayerSquare(); }

  /// 0: first animation frame, 1: second animation frame
  int GetPrisonerFrame() const noexcept { return m_prisoner_frame; }

  ///The heigh of the view displayed, in number of blocks
  int GetViewHeight() const noexcept { return 20; }

  ///The width of the view displayed, in number of blocks
  int GetViewWidth() const noexcept { return 20; }

  ///Press a key
  void PressKey(const Key key) { m_game.PressKeys( { key } ); }

  std::set<Key> RequestKeys();

  void RespondToCurrentSquare();

  ///Wait one turn
  void Tick();

  ///Toggles the enemy animation
  void ToggleEnemies() noexcept { m_enemy_frame = (m_enemy_frame + 1) % 2;  }

  ///Toggles the prisoner animation
  void TogglePrisoners() noexcept;

  private:
  int m_do_show_solution_cnt;

  /// 0: first animation frame, 1: second animation frame at which movement occurs
  int m_enemy_frame;

  ///The game logic
  Game m_game;

  /// 0: first animation frame, 1: second animation frame
  int m_prisoner_frame;

  ///Timepoint, in number of ticks
  int m_t;
};

Terminal create_test_terminal1();

Coordinat get_player_coordinat(const Terminal& t);

///Teleport to the closest maze square of the desired type
///by walking there without updating
void teleport_to(Terminal& t, const MazeSquare& s);

std::string to_str(const Terminal& t);

std::ostream& operator<<(std::ostream& os, const Terminal& t);

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKTERMINAL_H
