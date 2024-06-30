#ifndef WARNINGDIALOG_H
#define WARNINGDIALOG_H

#include <QDialog>

namespace Ui {
class WarningDialog;
}

class WarningDialog : public QDialog
{
    Q_OBJECT

public:
    bool canclose;
    explicit WarningDialog(int errtype, QWidget *parent = nullptr);
    ~WarningDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::WarningDialog *ui;
};

#endif // WARNINGDIALOG_H
