#ifndef SFMLMAZIAKGAMEDIALOG_H
#define SFMLMAZIAKGAMEDIALOG_H

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
  /// The window the game is rendered to
  sf::RenderWindow mWindow;
};

} //~namespace maziak
} //~namespace ribi

#endif // SFMLMAZIAKGAMEDIALOG_H
