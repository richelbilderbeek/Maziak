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
  const int block_width{rect().width() / m_view_width};
  const int block_height{rect().height() / m_view_height};
  //Draw maze
  {
    for (int row=0; row!=m_view_height; ++row)
    {
      for (int col=0; col!=m_view_width; ++col)
      {
        //col_maze and row_maze are the indices in the true/'non-visual' maze
        const int col_maze{get_player_x(m_game) - (m_view_width  / 2) + col};
        const int row_maze{get_player_y(m_game) - (m_view_height / 2) + row};
        const auto sprites = m_game.GetSprites(
          Coordinat(col_maze, row_maze),
          GetEnemiesFrame(),
          GetPrisonersFrame()
        );
        const QRect target_rect(
          col * block_width,
          row * block_height,
          block_width,
          block_height
        );
        for (const auto& s: sprites)
        {
          //painter.setBackgroundMode(Qt::BGMode::TransparentMode);
          painter.setBackgroundMode(Qt::BGMode::OpaqueMode);
          painter.drawPixmap(
            target_rect,
            m_sprites.Get(s)
          );
        }
      }
    }
  }
  mWindow.clear(sf::Color::Black); // Clear the window with black color
  for (int y = 0; y != get_n_rows(mGame); ++y)
  {
    for (int x = 0; x != get_n_cols(mGame); ++x)
    {
      const auto sprites = mGame.GetSprites(Coordinat(x, y));
      if (sprites.size() == 1 && sprites[0] == Sprite::wall)
      {
        sf::RectangleShape s;
        s.setPosition(x * 24, y * 24);
        s.setFillColor(sf::Color(255, 128, 0));
        s.setSize(sf::Vector2f(24, 24));
        mWindow.draw(s);
      }
    }
  }

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



