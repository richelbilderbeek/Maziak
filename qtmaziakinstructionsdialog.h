#ifndef QTMAZIAKINSTRUCTIONSDIALOG_H
#define QTMAZIAKINSTRUCTIONSDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
    class QtMaziakInstructionsDialog;
}

namespace ribi {

class QtMaziakInstructionsDialog : public QtHideAndShowDialog
{
    Q_OBJECT

public:
    explicit QtMaziakInstructionsDialog(QWidget *parent = 0);
    QtMaziakInstructionsDialog(const QtMaziakInstructionsDialog&) = delete;
    QtMaziakInstructionsDialog& operator=(const QtMaziakInstructionsDialog&) = delete;
    ~QtMaziakInstructionsDialog() noexcept;

private:
    Ui::QtMaziakInstructionsDialog *ui;
};

} //~namespace ribi

#endif // QTMAZIAKINSTRUCTIONSDIALOG_H
