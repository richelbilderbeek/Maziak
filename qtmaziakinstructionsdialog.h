#ifndef QTMAZIAKINSTRUCTIONSDIALOG_H
#define QTMAZIAKINSTRUCTIONSDIALOG_H

#include <QDialog>

namespace Ui {
    class QtMaziakInstructionsDialog;
}

namespace ribi {
namespace maziak {

class QtInstructionsDialog : public QDialog
{
    Q_OBJECT //!OCLINT

public:
    explicit QtInstructionsDialog(QWidget *parent = 0);
    QtInstructionsDialog(const QtInstructionsDialog&) = delete;
    QtInstructionsDialog& operator=(const QtInstructionsDialog&) = delete;
    ~QtInstructionsDialog() noexcept;

protected:
  void showEvent(QShowEvent *);

private:
    Ui::QtMaziakInstructionsDialog *ui;
};

} //~namespace maziak
} //~namespace ribi

#endif // QTMAZIAKINSTRUCTIONSDIALOG_H
