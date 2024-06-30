#include "passworddialog.h"
#include "ui_passworddialog.h"

#include <QMessageBox>
#include <infoeditpage.h>

PasswordDialog::PasswordDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PasswordDialog)
{
    Haspassed = false;
    ui->setupUi(this);
    setFixedSize(260,120);
    setWindowTitle("密码验证");
    setModal(true);
    ui->lineEdit->setPlaceholderText("请输入密码");
}

PasswordDialog::~PasswordDialog()
{
    delete ui;
}

void PasswordDialog::on_pushButton_clicked()
{
    if(ui->lineEdit->text() == "pkupku2024")
    {
        Haspassed = true;
        close();
    }
    else
    {
        QMessageBox::warning(this, "警告", "密码错误！", QMessageBox::Ok, QMessageBox::Ok);
        ui->lineEdit->clear();
    }
}

bool PasswordDialog::checkpass()
{
    return Haspassed;
}

