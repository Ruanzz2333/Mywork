#include "warningdialog.h"
#include "ui_warningdialog.h"

WarningDialog::WarningDialog(int errtype, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::WarningDialog)
{
    canclose = false;
    ui->setupUi(this);
    this->setFixedSize(191,115);
    this->setModal(true);
    this->setWindowTitle("Warning");
    switch(errtype)
    {
    case 1:
        ui->label->setText("数据加载失败,程序自动关闭");
        break;
    default:
        break;
    }
}

WarningDialog::~WarningDialog()
{
    delete ui;
}

void WarningDialog::on_pushButton_clicked()
{
    this->close();
    canclose = true;
}

