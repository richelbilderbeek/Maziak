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
