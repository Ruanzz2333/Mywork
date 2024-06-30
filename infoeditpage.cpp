#include "infoeditpage.h"
#include "ui_infoeditpage.h"

#include <QMessageBox>
#include <QStandardItem>

InfoEditPage::InfoEditPage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InfoEditPage)
{
    ui->setupUi(this);
    setFixedSize(280,340);
    setWindowTitle("添加/修改");
    setModal(true);
    ui->spinBox1->setRange(0,20);
    ui->spinBox2->setRange(0,100);
    ui->spinBox3->setRange(0,100);
    overallscore = 0;
    Dataline.clear();
}

InfoEditPage::~InfoEditPage()
{
    delete ui;
}

void InfoEditPage::calculateoverallscore()
{
    int score1 = ui->spinBox1->value();
    int score2 = ui->spinBox2->value();
    int score3 = ui->spinBox3->value();
    overallscore = std::round(score1 + score2*0.3 + score3*0.5);
    ui->Overallscore_line->setText(QString::number(overallscore));
}

void InfoEditPage::on_CancelButton_clicked()
{
    close();
}


void InfoEditPage::on_OkButton_clicked()
{
    QString ID = ui->ID_line->text();
    QString name = ui->Name_line->text();
    QString dep = ui->Dep_line->text();
    QString score1 = QString::number(ui->spinBox1->value());
    QString score2 = QString::number(ui->spinBox2->value());
    QString score3 = QString::number(ui->spinBox3->value());
    QString finalscore = ui->Overallscore_line->text();
    if( ID!="" &&
        name!="" &&
        dep!="" &&
        score1!="" &&
        score2!="" &&
        score3!="" &&
        finalscore!="")
    {
        Dataline.push_back(ID);
        Dataline.push_back(name);
        Dataline.push_back(dep);
        Dataline.push_back(score1);
        Dataline.push_back(score2);
        Dataline.push_back(score3);
        Dataline.push_back(finalscore);
        // studentsdata.push_back(Student(Dataline));
        close();
    }
    else
    {
        QMessageBox::warning(this, "提示", "不可填写空白内容！", QMessageBox::Ok, QMessageBox::Ok);
    }
}

QStringList& InfoEditPage::getdata()
{
    return Dataline;
}

void InfoEditPage::on_spinBox1_editingFinished()
{
    calculateoverallscore();
}


void InfoEditPage::on_spinBox2_editingFinished()
{
    calculateoverallscore();
}


void InfoEditPage::on_spinBox3_editingFinished()
{
    calculateoverallscore();
}
