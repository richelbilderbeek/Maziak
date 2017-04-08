#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtmaziakgamewondialog.h"

#include <cassert>
#include <iostream>

#include <boost/timer.hpp>

#include <QPainter>
#include <QPaintEvent>
#include <QTimer>

#include "ui_qtmaziakgamewondialog.h"

#pragma GCC diagnostic pop

ribi::maziak::QtGameWonDialog::QtGameWonDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtMaziakGameWonDialog),
  m_timer{new QTimer(this)},
  m_allow_close(false)
{
  ui->setupUi(this);

  m_timer->setInterval(2500);
  QObject::connect(
    m_timer,
    &QTimer::timeout,
    this,
    &ribi::maziak::QtGameWonDialog::onTimer
  );
  m_timer->start();
}

ribi::maziak::QtGameWonDialog::~QtGameWonDialog() noexcept
{
  delete ui;
}

void ribi::maziak::QtGameWonDialog::onTimer()
{
  m_allow_close = true;
  m_timer->stop();
}

void ribi::maziak::QtGameWonDialog::paintEvent(QPaintEvent*)
{
  QPainter painter(this);
  {
    //Top
    QPixmap pixmap(":/images/Congratulations.png");
    assert(!pixmap.isNull());
    painter.drawPixmap(ui->widget_top->geometry(),pixmap);
  }
  {
    //Center
    QPixmap pixmap(":/images/PlayerWon1.png");
    assert(!pixmap.isNull());
    painter.drawPixmap(ui->widget_center->geometry(),pixmap);
  }
  {
    //Bottom
    QPixmap pixmap(":/images/Congratulations.png");
    assert(!pixmap.isNull());
    painter.drawPixmap(ui->widget_bottom->geometry(),pixmap);
  }
}

void ribi::maziak::QtGameWonDialog::mousePressEvent(QMouseEvent*)
{
  if (m_allow_close) close();
}

void ribi::maziak::QtGameWonDialog::keyPressEvent(QKeyEvent*)
{
  if (m_allow_close) close();
}

