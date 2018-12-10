#ifndef SFMLMAZIAKGAMEDIALOG_H
#define SFMLMAZIAKGAMEDIALOG_H

#include "maziakgame.h"
#include <SFML/Graphics.hpp>

namespace ribi {
namespace maziak {

class SfmlGameDialog
{
public:
  SfmlGameDialog();

  ///Run the dialog, until the user closes it
  void Exec();

private:

  Game mGame;

  /// The window the game is rendered to
  sf::RenderWindow mWindow;

  /// Display the maze, enemies, player
  void DisplayGame();

  Stopwatch m_timer_animate_enemies;
  Stopwatch m_timer_animate_prisoners;
  Stopwatch m_timer_show_solution;

  const int m_view_width = 11;
  const int m_view_height = 11;

};

} //~namespace maziak
} //~namespace ribi

#endif // SFMLMAZIAKGAMEDIALOG_H
