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
};

} //~namespace maziak
} //~namespace ribi

#endif // SFMLMAZIAKGAMEDIALOG_H
