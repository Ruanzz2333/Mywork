#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <student.h>
#include <QCloseEvent>

class QStandardItemModel;
QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    static QString filename;

    //从"StudentInfo.txt"中读取存储的学生信息
    void ReadinData(const QString &fname);
    //保存数据
    void SaveData(const QString &fname);
    //保存数据到QVector
    void SavetoVector();
    //关闭窗口事件，可以询问是否退出
    void closeEvent(QCloseEvent *event);

private slots:
    void on_AddButton_clicked();

    void on_SaveButton_clicked();

    void on_DeleteButton_clicked();

    void on_LessButton_clicked();

    void on_GreaterButton_clicked();

    void on_EditButton_clicked();

private:
    Ui::Widget *ui;
    QStandardItemModel *datamodel;
    QVector<Student> studentsdata;
    bool HasSaved;

    friend class InfoEditPage;
};
#endif // WIDGET_H
