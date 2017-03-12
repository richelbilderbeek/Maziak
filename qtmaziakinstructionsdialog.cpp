#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"

#include "qtmaziakinstructionsdialog.h"
#include "ui_qtmaziakinstructionsdialog.h"

#pragma GCC diagnostic pop

ribi::QtMaziakInstructionsDialog::QtMaziakInstructionsDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtMaziakInstructionsDialog)
{
  ui->setupUi(this);
}

ribi::QtMaziakInstructionsDialog::~QtMaziakInstructionsDialog() noexcept
{
  delete ui;
}
