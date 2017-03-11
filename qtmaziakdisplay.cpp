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

#include <boost/scoped_ptr.hpp>

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
    m_image{QtGraphics().CreateImage(22 * ((9 * 2) + 1), 22 * ((9 * 2) + 1))},
    m_keys{},
    m_sprites{},
    m_timer_animate_enemies_and_prisoners{},
    m_timer_show_solution{}
{
  //Put the dialog in the screen center at 75% of fullscreen size
  const QRect screen = QApplication::desktop()->screenGeometry();
  this->setGeometry(0,0,screen.width() * 75 / 100,screen.height() * 75 / 100);
  this->move( screen.center() - this->rect().center() );
}

std::map<ribi::maziak::QtDisplay::WORD,ribi::maziak::Key> ribi::maziak::QtDisplay::CreateDefaultKeys() noexcept
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
  //std::clog << "."; //DEBUG

  const int block_width  = 22;
  const int block_height = 22;
  const int view_height{GetViewHeight()}; //Classic value is 9
  const int view_width{GetViewWidth()}; //Classic value is 9
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
        //Draw what's moving or standing on the floor
        const auto sprite_above_floor = main_dialog.GetSpriteAboveFloor(
          xVector,
          yVector
        );
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

  //Draw player
  {
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
  this->repaint();
  qApp->processEvents();
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
  painter.drawImage(0,0,m_image);
}

void ribi::maziak::QtDisplay::OnGameOver()
{
  this->hide();
  boost::scoped_ptr<QtMaziakGameOverDialog> f(new QtMaziakGameOverDialog(0));
  f->exec();
  close();
}

void ribi::maziak::QtDisplay::OnGameWon()
{
  this->hide();
  boost::scoped_ptr<QtMaziakGameWonDialog> f(new QtMaziakGameWonDialog);
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
