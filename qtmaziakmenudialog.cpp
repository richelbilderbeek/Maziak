

#include "qtmaziakmenudialog.h"

#include <cassert>
#include <iostream>
#include <stdexcept>

#include <memory>

#include <QDesktopWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QMouseEvent>

#include "about.h"
#include "maziakmenudialog.h"
#include "qtaboutdialog.h"
#include "qtmaziakcanvas.h"
#include "qtmaziakinstructionsdialog.h"
#include "maziakgame.h"
#include "qtmaziakdisplay.h"

#include "ui_qtmaziakmenudialog.h"



ribi::maziak::QtMenuDialog::QtMenuDialog(
  const int rng_seed,
  QWidget *parent
) :
    QDialog(parent),
    ui(new Ui::QtMaziakMenuDialog),
    m_allow_popups{true},
    m_difficulty(Difficulty::easy),
    m_rng_seed{rng_seed}
{
  ui->setupUi(this);

  //Put the dialog in the screen's center
  const QRect screen = QApplication::desktop()->screenGeometry();
  this->move( screen.center() - this->rect().center() );
}

ribi::maziak::QtMenuDialog::~QtMenuDialog() noexcept
{
  delete ui;
}

void ribi::maziak::QtMenuDialog::mousePressEvent(QMouseEvent * event)
{
  if (ui->widget_easy->geometry().contains(
    event->x(), event->y()))
  {
    m_difficulty = Difficulty::easy;
    repaint();
    return;
  }
  if (ui->widget_medium->geometry().contains(
    event->x(), event->y()))
  {
    m_difficulty = Difficulty::medium;
    repaint();
    return;
  }
  if (ui->widget_hard->geometry().contains(
    event->x(), event->y()))
  {
    m_difficulty = Difficulty::hard;
    repaint();
    return;
  }
  if (ui->widget_start->geometry().contains(
    event->x(), event->y()))
  {
    OnStart(); return;
  }
  if (ui->widget_instructions->geometry().contains(
    event->x(), event->y()))
  {
    OnInstructions();
    return;
  }
  if (ui->widget_about->geometry().contains(
    event->x(), event->y()))
  {
    OnAbout();
    return;
  }
  if (ui->widget_quit->geometry().contains(
    event->x(), event->y()))
  {
    close();
  }
}

void ribi::maziak::QtMenuDialog::keyPressEvent(QKeyEvent * event)
{
  switch (event->key())
  {
    case Qt::Key_Up:
    {
      switch (m_difficulty)
      {
        case Difficulty::easy: return;
        case Difficulty::medium: m_difficulty = Difficulty::easy; repaint(); return;
        case Difficulty::hard: m_difficulty = Difficulty::medium; repaint(); return;
      }
      assert(!"Should not get here"); //!OCLINT accepted idiom
    }
    case Qt::Key_Down:
    {
      switch (m_difficulty)
      {
        case Difficulty::easy: m_difficulty = Difficulty::medium; repaint(); return;
        case Difficulty::medium: m_difficulty = Difficulty::hard; repaint(); return;
        case Difficulty::hard: return;
      }
      assert(!"Should not get here"); //!OCLINT accepted idiom
    }
    case Qt::Key_S: OnStart(); break;
    case Qt::Key_I: OnInstructions(); break;
    case Qt::Key_A: OnAbout(); break;
    case Qt::Key_Q:
    case Qt::Key_Escape:
      close(); return;
    default:
      break;
  }
}

void ribi::maziak::QtMenuDialog::paintEvent(QPaintEvent*)
{
  QPainter painter(this);
  {
    QPixmap background(":/maziak/pics/MaziakBackground.png");
    painter.drawPixmap(rect(),background);
  }

  {
    //Top left
    QPixmap pixmap;
    switch (m_difficulty)
    {
      case Difficulty::easy:
        pixmap = QPixmap(":/maziak/pics/PlayerWon1.png");
        break;
      case Difficulty::medium:
        pixmap = QPixmap(":/maziak/pics/PlayerLookDown.png");
        break;
      case Difficulty::hard:
        pixmap = QPixmap(":/maziak/pics/PlayerScared.png");
        break;
      default:
        assert(!"Should not get here");
    }
    assert(!pixmap.isNull());
    painter.drawPixmap(ui->widget_top_left->geometry(),pixmap);
  }
  {
    //Top right
    QPixmap pixmap;
    switch (m_difficulty)
    {
      case Difficulty::easy:
        pixmap = QPixmap(":/maziak/pics/Fight2.png");
        break;
      case Difficulty::medium:
        pixmap = QPixmap(":/maziak/pics/Fight3.png");
        break;
      case Difficulty::hard:
        pixmap = QPixmap(":/maziak/pics/Fight4.png");
        break;
      default:
        assert(!"Should not get here");
    }
    assert(!pixmap.isNull());
    painter.drawPixmap(ui->widget_top_right->geometry(),pixmap);
  }
  {
    //Easy
    QPixmap pixmap(m_difficulty == Difficulty::easy
      ? ":/maziak/pics/Easy_selected.png"
      : ":/maziak/pics/Easy_not_selected.png");
    assert(!pixmap.isNull());
    painter.drawPixmap(ui->widget_easy->geometry(),pixmap);
  }
  {
    //Medium
    QPixmap pixmap(m_difficulty == Difficulty::medium
      ? ":/maziak/pics/Medium_selected.png"
      : ":/maziak/pics/Medium_not_selected.png");
    assert(!pixmap.isNull());

    painter.drawPixmap(ui->widget_medium->geometry(),pixmap);
  }
  {
    //Hard
    QPixmap pixmap(m_difficulty == Difficulty::hard
      ? ":/maziak/pics/Hard_selected.png"
      : ":/maziak/pics/Hard_not_selected.png");
    assert(!pixmap.isNull());
    painter.drawPixmap(ui->widget_hard->geometry(),pixmap);
  }
  {
    //Start
    QPixmap pixmap(":/maziak/pics/Start.png");
    assert(!pixmap.isNull());
    painter.drawPixmap(ui->widget_start->geometry(),pixmap);
  }
  {
    //Instructions
    QPixmap pixmap(":/maziak/pics/Instructions.png");
    assert(!pixmap.isNull());
    painter.drawPixmap(ui->widget_instructions->geometry(),pixmap);
  }
  {
    //About
    QPixmap pixmap(":/maziak/pics/About.png");
    assert(!pixmap.isNull());
    painter.drawPixmap(ui->widget_about->geometry(),pixmap);
  }
  {
    //Quit
    QPixmap pixmap(":/maziak/pics/Quit.png");
    assert(!pixmap.isNull());
    painter.drawPixmap(ui->widget_quit->geometry(),pixmap);
  }


}

int ribi::maziak::QtMenuDialog::GetMazeSize() const
{
  switch (m_difficulty)
  {
    case Difficulty::easy  : return  19;
    //case Difficulty::easy  : return  99;
    case Difficulty::medium: return 499;
    case Difficulty::hard  : return 999;
  }
  assert(!"Should not get here");
  throw std::logic_error("Unsupported value of mDifficulty");
}

void ribi::maziak::QtMenuDialog::OnAbout()
{
  this->hide();
  About a = MenuDialog().GetAbout();
  std::unique_ptr<QtAboutDialog> d(new QtAboutDialog(a));
  d->setStyleSheet(
    "background: url(:/maziak/pics/MaziakBackground.png) repeat center center fixed;"
  );
  if (m_allow_popups)
  {
    d->exec();
  }
  else
  {
    d->show();
  }
  this->show();
}

void ribi::maziak::QtMenuDialog::OnInstructions()
{
  this->hide();
  std::unique_ptr<QtInstructionsDialog> d(new QtInstructionsDialog);
  if (m_allow_popups)
  {
    d->exec();
  }
  else
  {
    d->show();
  }
  this->show();
}

void ribi::maziak::QtMenuDialog::OnStart()
{
  this->hide();
  QtDisplay d(
    GetMazeSize(),
    GetMazeSize(),
    std::abs(m_rng_seed), //m_rng_seed may be any number.
    11,
    11
  );
  d.showFullScreen();
  if (m_allow_popups)
  {
    d.exec();
  }
  else
  {
    d.show();
  }
  this->show();
}
