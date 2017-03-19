#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
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
#include "maziakmaindialog.h"
#include "qtmaziakdisplay.h"

#include "ui_qtmaziakmenudialog.h"

#pragma GCC diagnostic pop

ribi::maziak::QtMaziakMenuDialog::QtMaziakMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtMaziakMenuDialog),
    m_difficulty(Difficulty::easy)
{
  ui->setupUi(this);

  //Put the dialog in the screen's center
  const QRect screen = QApplication::desktop()->screenGeometry();
  this->move( screen.center() - this->rect().center() );
}

ribi::maziak::QtMaziakMenuDialog::~QtMaziakMenuDialog() noexcept
{
  delete ui;
}

void ribi::maziak::QtMaziakMenuDialog::mousePressEvent(QMouseEvent * event)
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

void ribi::maziak::QtMaziakMenuDialog::keyPressEvent(QKeyEvent * event)
{
  switch (event->key())
  {
    case Qt::Key_Up: case Qt::Key_Left:
    {
      switch (m_difficulty)
      {
        case Difficulty::easy: return;
        case Difficulty::medium: m_difficulty = Difficulty::easy; repaint(); return;
        case Difficulty::hard: m_difficulty = Difficulty::medium; repaint(); return;
        default: assert(!"Should not get here");
      }
    }
    case Qt::Key_Down: case Qt::Key_Right:
    {
      switch (m_difficulty)
      {
        case Difficulty::easy: m_difficulty = Difficulty::medium; repaint(); return;
        case Difficulty::medium: m_difficulty = Difficulty::hard; repaint(); return;
        case Difficulty::hard: return;
        default: assert(!"Should not get here");
      }
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

void ribi::maziak::QtMaziakMenuDialog::paintEvent(QPaintEvent*)
{
  QPainter painter(this);
  {
    QPixmap background(":/images/MaziakBackground.png");
    painter.drawPixmap(rect(),background);
  }

  {
    //Top left
    QPixmap pixmap;
    switch (m_difficulty)
    {
      case Difficulty::easy:
        pixmap = QPixmap(":/images/PlayerWon1.png");
        break;
      case Difficulty::medium:
        pixmap = QPixmap(":/images/PlayerLookDown.png");
        break;
      case Difficulty::hard:
        pixmap = QPixmap(":/images/PlayerScared.png");
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
        pixmap = QPixmap(":/images/Fight2.png");
        break;
      case Difficulty::medium:
        pixmap = QPixmap(":/images/Fight3.png");
        break;
      case Difficulty::hard:
        pixmap = QPixmap(":/images/Fight4.png");
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
      ? ":/images/Easy_selected.png"
      : ":/images/Easy_not_selected.png");
    assert(!pixmap.isNull());
    painter.drawPixmap(ui->widget_easy->geometry(),pixmap);
  }
  {
    //Medium
    QPixmap pixmap(m_difficulty == Difficulty::medium
      ? ":/images/Medium_selected.png"
      : ":/images/Medium_not_selected.png");
    assert(!pixmap.isNull());

    painter.drawPixmap(ui->widget_medium->geometry(),pixmap);
  }
  {
    //Hard
    QPixmap pixmap(m_difficulty == Difficulty::hard
      ? ":/images/Hard_selected.png"
      : ":/images/Hard_not_selected.png");
    assert(!pixmap.isNull());
    painter.drawPixmap(ui->widget_hard->geometry(),pixmap);
  }
  {
    //Start
    QPixmap pixmap(":/images/Start.png");
    assert(!pixmap.isNull());
    painter.drawPixmap(ui->widget_start->geometry(),pixmap);
  }
  {
    //Instructions
    QPixmap pixmap(":/images/Instructions.png");
    assert(!pixmap.isNull());
    painter.drawPixmap(ui->widget_instructions->geometry(),pixmap);
  }
  {
    //About
    QPixmap pixmap(":/images/About.png");
    assert(!pixmap.isNull());
    painter.drawPixmap(ui->widget_about->geometry(),pixmap);
  }
  {
    //Quit
    QPixmap pixmap(":/images/Quit.png");
    assert(!pixmap.isNull());
    painter.drawPixmap(ui->widget_quit->geometry(),pixmap);
  }


}

int ribi::maziak::QtMaziakMenuDialog::GetMazeSize() const
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

void ribi::maziak::QtMaziakMenuDialog::OnAbout()
{
  About a = MenuDialog().GetAbout();
  std::unique_ptr<QtAboutDialog> d(new QtAboutDialog(a));
  this->ShowChild(d.get());
}

void ribi::maziak::QtMaziakMenuDialog::OnInstructions()
{
  std::unique_ptr<QtMaziakInstructionsDialog> d(new QtMaziakInstructionsDialog);
  this->ShowChild(d.get());
}

void ribi::maziak::QtMaziakMenuDialog::OnStart()
{
  QtDisplay d;
  MainDialog w(GetMazeSize());
  w.SetDisplay(&d);
  d.DoDisplay(w);
  {
    QRect screen = QApplication::desktop()->screenGeometry();
    d.move( screen.center() - d.rect().center() );
  }
  d.show();
  w.Execute();
}
