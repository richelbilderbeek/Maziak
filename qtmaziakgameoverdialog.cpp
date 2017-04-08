#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtmaziakgameoverdialog.h"

#include <cassert>

#include <boost/timer.hpp>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>

#include "ui_qtmaziakgameoverdialog.h"
#pragma GCC diagnostic pop

ribi::maziak::QtGameOverDialog::QtGameOverDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtMaziakGameOverDialog),
  m_timer{new QTimer(this)},
  m_allow_close(false)
{
  ui->setupUi(this);
  m_timer->setInterval(2500);
  QObject::connect(
    m_timer,&QTimer::timeout,
    this,&ribi::maziak::QtGameOverDialog::onTimer
  );
  m_timer->start();
}

ribi::maziak::QtGameOverDialog::~QtGameOverDialog() noexcept
{
  delete ui;
}

void ribi::maziak::QtGameOverDialog::onTimer()
{
  m_allow_close = true;
  m_timer->stop();
}

void ribi::maziak::QtGameOverDialog::paintEvent(QPaintEvent*)
{
  QPainter painter(this);
  {
    //Top
    QPixmap pixmap(":/images/GameOver.png");
    assert(!pixmap.isNull());
    painter.drawPixmap(ui->widget_top->geometry(),pixmap);
  }
  {
    //Center
    QPixmap pixmap(":/images/Rip.png");
    assert(!pixmap.isNull());
    painter.drawPixmap(ui->widget_center->geometry(),pixmap);
  }
  {
    //Bottom
    QPixmap pixmap(":/images/GameOver.png");
    assert(!pixmap.isNull());
    painter.drawPixmap(ui->widget_bottom->geometry(),pixmap);
  }
}

void ribi::maziak::QtGameOverDialog::mousePressEvent(QMouseEvent*)
{
  if (m_allow_close) close();
}

void ribi::maziak::QtGameOverDialog::keyPressEvent(QKeyEvent*)
{
  if (m_allow_close) close();
}


