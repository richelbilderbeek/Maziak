#include "sfmlmaziakgamedialog.h"

ribi::maziak::SfmlGameDialog::SfmlGameDialog()
  : mGame(CreateTestGame1()),
    mWindow(
      sf::VideoMode(
        1024,//static_cast<unsigned int>(11 * 24), //11: n cols, 24: sprite width
        768 //static_cast<unsigned int>(11 * 24)  //11: n rows, 24: sprite height
      ),
      "Maziak",
      sf::Style::Default
    )
{

}

void ribi::maziak::SfmlGameDialog::DisplayGame()
{
  mWindow.clear(sf::Color::Black); // Clear the window with black color

  sf::RectangleShape s;
  s.setPosition(100, 100);
  s.setFillColor(sf::Color(255, 128, 0));
  s.setSize(sf::Vector2f(100, 100));
  mWindow.draw(s);

  mWindow.display();
}

void ribi::maziak::SfmlGameDialog::Exec()
{
  while (mWindow.isOpen())
  {
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
      switch (event.type)
      {
        case sf::Event::Closed:
          mWindow.close();
          break;

        default:
          // Do nothing by default
          break;
      }
    }
    DisplayGame();
  }
}



