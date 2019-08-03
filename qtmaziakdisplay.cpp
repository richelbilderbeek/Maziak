



#include "qtmaziakdisplay.h"

#include <algorithm>
#include <cassert>
#include <cmath>

#include <iostream>
#include <stdexcept>
#include <vector>

#include <memory>
#include <boost/timer.hpp>
#include <gsl/gsl_assert>
#include <QDesktopWidget>
#include <QApplication>
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include "maziakhelper.h"
#include "maziakintmaze.h"
#include "maziakmaze.h"
#include "qtmaziaksprites.h"
#include "qtmaziakgameoverdialog.h"
#include "qtmaziakgamewondialog.h"
#include "maziaksolutionmaze.h"



ribi::maziak::QtDisplay::QtDisplay(
  const int n_cols,
  const int n_rows,
  const int rng_seed,
  const int view_width,
  const int view_height,
  QWidget *parent
) : QDialog(parent),
    m_game(Maze(n_cols, n_rows, rng_seed)),
    m_keys{},
    m_sprites{},
    m_timer_animate_prisoners{},
    m_timer_show_solution{},
    m_view_height{view_height},
    m_view_width{view_width}
{
  {
    QTimer * const timer{new QTimer(this)};
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(Tick()));
    timer->setInterval(1000 / 60);
    timer->start();
  }
  {
    QTimer * const timer{new QTimer(this)};
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(Respond()));
    timer->setInterval(100);
    timer->start();
  }
}

std::map<ribi::maziak::QtDisplay::WORD,ribi::maziak::Key>
ribi::maziak::CreateDefaultKeys() noexcept
{
  std::map<QtDisplay::WORD, Key> m;
  m.insert(std::make_pair(Qt::Key_Up   ,Key::up   ));
  m.insert(std::make_pair(Qt::Key_Right,Key::right));
  m.insert(std::make_pair(Qt::Key_Down ,Key::down ));
  m.insert(std::make_pair(Qt::Key_Left ,Key::left ));
  return m;
}

bool ribi::maziak::QtDisplay::GetDoShowSolution()
{
  return m_timer_show_solution.GetElapsedSecs() < 5.0;
}

int ribi::maziak::get_n_cols(const QtDisplay& q) noexcept
{
  return get_n_cols(q.GetGame());
}

int ribi::maziak::get_n_rows(const QtDisplay& q) noexcept
{
  return get_n_rows(q.GetGame());
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
  Respond();
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

int ribi::maziak::QtDisplay::GetEnemiesFrame() noexcept
{
  static int frame = 0;
  if (m_timer_animate_enemies.GetElapsedSecs() > 0.9)
  {
    ++frame;
    m_timer_animate_enemies = Stopwatch();
    m_game.MakeEnemiesMove(m_view_width,m_view_height);
  }
  return frame;
}

int ribi::maziak::QtDisplay::GetPrisonersFrame() noexcept
{
  static int frame = 0;
  if (m_timer_animate_prisoners.GetElapsedSecs() > 0.8)
  {
    frame = (frame + 1) % 2;
    m_timer_animate_prisoners = Stopwatch();
  }
  //The prisoners have two frames
  assert(frame == 0 || frame == 1);
  return frame;
}

void ribi::maziak::QtDisplay::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
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
        assert(GetPrisonersFrame() == 0 || GetPrisonersFrame() == 1);
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
}

void ribi::maziak::QtDisplay::OnGameOver()
{
  this->hide();
  QtGameOverDialog * const f{new QtGameOverDialog(this)};
  f->show();
  f->exec();
  close();
}

void ribi::maziak::QtDisplay::OnGameWon()
{
  this->hide();
  QtGameWonDialog * const f{new QtGameWonDialog(this)};
  this->hide();
  f->show();
  f->exec();
  close();
}

void ribi::maziak::QtDisplay::Respond()
{
  m_game.AnimateFighting();
  m_game.PressKeys(m_keys);
  m_game.RespondToCurrentSquare();
  if (m_game.GetState() == GameState::has_won)
  {
    OnGameWon();
    return;
  }
  if (m_game.GetState() == GameState::game_over)
  {
    OnGameOver();
    return;
  }
}

void ribi::maziak::QtDisplay::StartShowSolution()
{
  m_timer_show_solution = Stopwatch();
}

void ribi::maziak::QtDisplay::Tick()
{
  this->repaint();
}
