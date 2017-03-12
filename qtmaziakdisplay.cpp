#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtmaziakdisplay.h"

#include <algorithm>
#include <cassert>
#include <cmath>

#include <iostream>
#include <stdexcept>
#include <vector>

#include <memory>
#include <gsl/gsl_assert>
#include <QDesktopWidget>
#include <QApplication>
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include "maziakhelper.h"
#include "maziakintmaze.h"
#include "maziakmaze.h"
#include "maziaksprites.h"
#include "qtmaziakgameoverdialog.h"
#include "qtmaziakgamewondialog.h"
#include "qtgraphics.h"
#include "maziaksolutionmaze.h"
#include "maziakmaindialog.h"


#pragma GCC diagnostic pop

ribi::maziak::QtDisplay::QtDisplay(QWidget *parent)
  : QWidget(parent),
    m_image{QtGraphics().CreateImage(9 * 24, 9 * 24)},
    m_keys{},
    m_sprites{},
    m_timer_animate_enemies_and_prisoners{},
    m_timer_show_solution{}
{
  #ifdef DO_CALL_VIRTUAL_FUNCTIONS_IN_CONSTRUCRTOR
  {
    const int view_height{GetViewHeight()}; //Classic value is 9
    const int view_width{GetViewWidth()};
    assert(m_image.height() == m_sprites.GetHeight() * view_height);
    assert(m_image.width() == m_sprites.GetWidth() * view_width);
  }
  #endif

  //Put the dialog in the screen center at 75% of fullscreen size
  const QRect screen = QApplication::desktop()->screenGeometry();
  this->setGeometry(0,0,screen.width() * 75 / 100,screen.height() * 75 / 100);
  this->move( screen.center() - this->rect().center() );
}

std::map<ribi::maziak::QtDisplay::WORD,ribi::maziak::Key>
ribi::maziak::QtDisplay::CreateDefaultKeys() noexcept
{
  std::map<WORD,Key> m;
  m.insert(std::make_pair(Qt::Key_Up   ,Key::up   ));
  m.insert(std::make_pair(Qt::Key_Right,Key::right));
  m.insert(std::make_pair(Qt::Key_Down ,Key::down ));
  m.insert(std::make_pair(Qt::Key_Left ,Key::left ));
  return m;
}

void ribi::maziak::QtDisplay::DoDisplay(const MainDialog& main_dialog)
{
  Expects(m_image.height() == m_sprites.GetHeight() * GetViewHeight());
  Expects(m_image.width() == m_sprites.GetWidth() * GetViewWidth());
  DisplaySpritesFloor(main_dialog);
  DisplaySpritesAboveFloor(main_dialog);
  DisplayPlayer(main_dialog);
  this->repaint();
  qApp->processEvents();
}

void ribi::maziak::QtDisplay::DisplaySpritesFloor(
  const MainDialog& main_dialog)
{
  Expects(m_image.height() == m_sprites.GetHeight() * GetViewHeight());
  Expects(m_image.width() == m_sprites.GetWidth() * GetViewWidth());
  const int view_height{GetViewHeight()}; //Classic value is 9
  const int view_width{GetViewWidth()}; //Classic value is 9
  const int block_height{m_sprites.GetHeight()};
  const int block_width{m_sprites.GetWidth()};
  //Draw maze
  {
    for (int y=0; y!=view_height; ++y)
    {
      for (int x=0; x!=view_width; ++x)
      {
        //xVector and yVector are the indices in the non-visual maze 2D std::vector
        const int xVector = main_dialog.GetX() - (view_width  / 2) + x;
        const int yVector = main_dialog.GetY() - (view_height / 2) + y;
        //Draw the floor tile
        const auto pixmap_floor = m_sprites.Get(
          main_dialog.GetSpriteFloor(
            xVector,
            yVector
          )
        );
         QtGraphics().DrawImage(
          m_image,
          pixmap_floor.toImage(),
          (x * block_width )+0,
          (y * block_height)+0
        );
      }
    }
  }
}

void ribi::maziak::QtDisplay::DisplaySpritesAboveFloor(
  const MainDialog& main_dialog)
{
  Expects(m_image.height() == m_sprites.GetHeight() * GetViewHeight());
  Expects(m_image.width() == m_sprites.GetWidth() * GetViewWidth());
  const int view_height{GetViewHeight()}; //Classic value is 9
  const int view_width{GetViewWidth()}; //Classic value is 9
  const int block_height{m_sprites.GetHeight()};
  const int block_width{m_sprites.GetWidth()};
  {
    for (int y=0; y!=view_height; ++y)
    {
      for (int x=0; x!=view_width; ++x)
      {
        //xVector and yVector are the indices in the non-visual maze 2D std::vector
        const int xVector = main_dialog.GetX() - (view_width  / 2) + x;
        const int yVector = main_dialog.GetY() - (view_height / 2) + y;

        //Draw what's moving or standing on the floor
        const auto sprite_above_floor = main_dialog.GetSpriteAboveFloor(
          xVector,
          yVector
        );
        if (sprite_above_floor == Sprite::transparent) continue;
        const auto pixmap_above_floor = m_sprites.Get(sprite_above_floor);
        assert(IsValidFormat(pixmap_above_floor.toImage().format()));
        QtGraphics().DrawImage(
          m_image,
          pixmap_above_floor.toImage(),
          (x * block_width )+0,
          (y * block_height)+0
        );
      }
    }
  }

}

void ribi::maziak::QtDisplay::DisplayPlayer(const MainDialog& main_dialog)
{
  Expects(m_image.height() == m_sprites.GetHeight() * GetViewHeight());
  Expects(m_image.width() == m_sprites.GetWidth() * GetViewWidth());
  const int view_height{GetViewHeight()}; //Classic value is 9
  const int view_width{GetViewWidth()}; //Classic value is 9
  const int block_height{m_sprites.GetHeight()};
  const int block_width{m_sprites.GetWidth()};

  const auto player = m_sprites.Get(
    main_dialog.GetSpritePlayer()
  );
  QtGraphics().DrawImage(
    m_image,
    player.toImage(),
    ((view_width  / 2) * block_width ) + 0,
    ((view_height / 2) * block_height) + 0
  );
}

bool ribi::maziak::QtDisplay::GetDoShowSolution()
{
  return m_timer_show_solution.GetElapsedSecs() < 5.0;
}

void ribi::maziak::QtDisplay::resizeEvent(QResizeEvent*)
{
  this->repaint();
}

void ribi::maziak::QtDisplay::keyPressEvent(QKeyEvent* e)
{
  switch (e->key())
  {
    case Qt::Key_Up   : m_keys.insert(Key::up   ); break;
    case Qt::Key_Right: m_keys.insert(Key::right); break;
    case Qt::Key_Down : m_keys.insert(Key::down ); break;
    case Qt::Key_Left : m_keys.insert(Key::left ); break;
  }
}

void ribi::maziak::QtDisplay::keyReleaseEvent(QKeyEvent * e)
{
  switch (e->key())
  {
    case Qt::Key_Up   : m_keys.erase(Key::up   ); break;
    case Qt::Key_Right: m_keys.erase(Key::right); break;
    case Qt::Key_Down : m_keys.erase(Key::down ); break;
    case Qt::Key_Left : m_keys.erase(Key::left ); break;
  }
}

bool ribi::maziak::QtDisplay::MustAnimateEnemiesAndPrisoners() noexcept
{
  if (m_timer_animate_enemies_and_prisoners.GetElapsedSecs() > 0.9)
  {
    m_timer_animate_enemies_and_prisoners = Stopwatch();
    return true;
  }
  return false;
}

void ribi::maziak::QtDisplay::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.drawImage(this->rect(),m_image);
}

void ribi::maziak::QtDisplay::OnGameOver()
{
  this->hide();
  std::unique_ptr<QtMaziakGameOverDialog> f(new QtMaziakGameOverDialog(0));
  f->exec();
  close();
}

void ribi::maziak::QtDisplay::OnGameWon()
{
  this->hide();
  std::unique_ptr<QtMaziakGameWonDialog> f(new QtMaziakGameWonDialog);
  this->hide();
  f->exec();
  close();
}

std::set<ribi::maziak::Key> ribi::maziak::QtDisplay::RequestKeys()
{
  return m_keys;
}

void ribi::maziak::QtDisplay::StartShowSolution()
{
  m_timer_show_solution = Stopwatch();
}
