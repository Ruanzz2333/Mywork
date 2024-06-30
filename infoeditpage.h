#ifndef INFOEDITPAGE_H
#define INFOEDITPAGE_H

#include <QDialog>

namespace Ui {
class InfoEditPage;
}

class InfoEditPage : public QDialog
{
    Q_OBJECT

public:
    explicit InfoEditPage(QWidget *parent = nullptr);
    ~InfoEditPage();
    void calculateoverallscore();//计算总评成绩
    QStringList& getdata();//在其他类中读取Dataline

    friend class Widget;

private slots:
    void on_CancelButton_clicked();
    void on_OkButton_clicked();
    void on_spinBox1_editingFinished();
    void on_spinBox2_editingFinished();
    void on_spinBox3_editingFinished();

private:
    Ui::InfoEditPage *ui;
    int overallscore;//存储总评成绩
    QStringList Dataline;//存储填写入的全部信息
};

#endif // INFOEDITPAGE_H
