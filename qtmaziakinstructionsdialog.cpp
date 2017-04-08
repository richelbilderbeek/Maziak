#include "qtmaziakinstructionsdialog.h"
#include "ui_qtmaziakinstructionsdialog.h"

ribi::maziak::QtInstructionsDialog::QtInstructionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtMaziakInstructionsDialog)
{
  ui->setupUi(this);
}

ribi::maziak::QtInstructionsDialog::~QtInstructionsDialog() noexcept
{
  delete ui;
}

void ribi::maziak::QtInstructionsDialog::showEvent(QShowEvent *)
{
  //Rescale the pixmaps in a blocky retro way
  for (auto p : { ui->label } )
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
