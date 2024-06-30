#ifndef PASSWORDDIALOG_H
#define PASSWORDDIALOG_H

#include <QDialog>

namespace Ui {
class PasswordDialog;
}

class PasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PasswordDialog(QWidget *parent = nullptr);
    ~PasswordDialog();
    bool checkpass();//用于在其他类中获取Haspassed的值

private slots:
    void on_pushButton_clicked();

private:
    Ui::PasswordDialog *ui;
    bool Haspassed;//标记是否通过验证
};


#endif // PASSWORDDIALOG_H
