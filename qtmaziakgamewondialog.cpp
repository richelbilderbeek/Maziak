

#include "qtmaziakgamewondialog.h"

#include <cassert>
#include <iostream>

#include <boost/timer.hpp>

#include <QPainter>
#include <QPaintEvent>
#include <QTimer>

#include "ui_qtmaziakgamewondialog.h"



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

void ribi::maziak::QtGameWonDialog::mousePressEvent(QMouseEvent*)
{
  if (m_allow_close) close();
}

void ribi::maziak::QtGameWonDialog::keyPressEvent(QKeyEvent*)
{
  if (m_allow_close) close();
}

void ribi::maziak::QtGameWonDialog::showEvent(QShowEvent *)
{
  //Rescale the pixmaps in a blocky retro way
  for (auto p : { ui->label_picture, ui->label_text } )
  {
    p->setPixmap(
      p->pixmap()->scaled(
        p->width(),
        p->height(),
        Qt::KeepAspectRatio, Qt::FastTransformation
      )
    );
  }
}



