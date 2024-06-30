#include "widget.h"
#include "ui_widget.h"

#include <QFile>
#include <QDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QStandardItemModel>
#include <QCloseEvent>
#include <student.h>
#include <passworddialog.h>
#include <ui_passworddialog.h>
#include <infoeditpage.h>
#include <ui_infoeditpage.h>

Widget::Widget(QWidget *parent)//主窗口构造函数
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    HasSaved = true;
    ui->setupUi(this);
    //固定主窗口大小
    setFixedSize(810,550);
    //设置主表格属性
    setWindowTitle("Student Management");//标题名称
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);//可以选中单个
    show();//显示主界面
    //读取数据
    ReadinData(filename);
}

Widget::~Widget()//主窗口析构函数
{
    studentsdata.clear();
    delete ui;
}

void Widget::closeEvent(QCloseEvent *event)//窗口关闭时询问是否退出
{ //窗口关闭时询问是否退出
    if(HasSaved)//如果已经保存过数据了，直接询问是否退出
    {
        //消息提示：确定要退出本系统吗？
        QMessageBox::StandardButton result = QMessageBox::question(this, "确认", "确定要退出本系统吗？", QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes);
        if (result == QMessageBox::Yes)
            event->accept();//退出
        else
            event->ignore();//不退出
    }
    else//没有保存，先询问是否保存
    {
        //警告：尚未保存
        QMessageBox::StandardButton result = QMessageBox::warning(this, "注意", "您尚未保存，直接退出将丢失数据", QMessageBox::Save|QMessageBox::Discard|QMessageBox::Cancel, QMessageBox::Save);
        switch (result)
        {
        case QMessageBox::Save://需要保存
            event->ignore();//不关闭程序
            qInfo()<<"Saving...";
            //保存数据
            SaveData(filename);
            close();//关闭主窗口
            break;
        case QMessageBox::Discard://忽略，不保存直接退出
            event->accept();
            break;
        case QMessageBox::Cancel://取消，不关闭程序也不保存
            event->ignore();
            break;
        default:
            break;
        }
    }
}

void Widget::ReadinData(const QString &fname)//从文件读取数据
{
    QFile file(fname);// Open File
    if(!file.open(QIODevice::ReadOnly))// Open Failed
    {
        qInfo()<<fname<<"open failed";
        QMessageBox::warning(this, "注意", "数据加载失败，程序将自动关闭", QMessageBox::Ok, QMessageBox::Ok);
        close();//关闭主界面
    }

    QTextStream stream(&file);
    //读取表头
    QStringList Headerline = stream.readLine().split(" ");
    qInfo()<<Headerline;
    //设置表头
    datamodel = new QStandardItemModel(this);
    ui->tableView->setModel(datamodel);
    datamodel->setHorizontalHeaderLabels(Headerline);
    //读取数据并填入
    while(!stream.atEnd())
    {
        //读取一行，存到studentsdata中
        QStringList Dataline = stream.readLine().split(" ");
        studentsdata.push_back(Student(Dataline));
        //在屏幕上显示
        QList<QStandardItem*> items;
        for(QString tmpdata : Dataline)
        {
            QStandardItem *tmpitem = new QStandardItem();
            tmpitem->setText(tmpdata);//设置文字
            tmpitem->setTextAlignment(Qt::AlignCenter);//居中对齐
            items.push_back(tmpitem);
        }
        datamodel->appendRow(items);
    }
}

void Widget::SavetoVector()//缓存数据
{
    // 先清空QVector
    studentsdata.clear();
    int colnum = datamodel->columnCount();//总列数
    for(int row = 0; row < datamodel->rowCount(); row++)
    {
        QStringList toVector;
        for(int i = 0; i < colnum; i++)
        {
            toVector.push_back(datamodel->item(row,i)->text());//向临时List中推入row行i列的文本
        }
        studentsdata.push_back(Student(toVector));//将完整List填入Student的对象，并且推入QVector
    }
}

void Widget::SaveData(const QString &fname)//向文件中保存数据
{
    if(!HasSaved)//如果没保存，操作保存
    {
        qInfo()<<"Saving...";
        QFile file(fname);// Open File
        if(!file.open(QIODevice::WriteOnly))// Open Failed
        {
            qInfo()<<fname<<"Save failed";
            QMessageBox::warning(this, "注意", "保存失败，文件不存在，请检查后重试", QMessageBox::Ok, QMessageBox::Ok);
        }

        QTextStream stream(&file);
        //保存表头
        QString HeaderLine;
        int colnum = datamodel->columnCount();
        for(int i = 0; i < colnum; i++)
        {
            HeaderLine += datamodel->horizontalHeaderItem(i)->text();
            if(i != colnum-1)
                HeaderLine += " ";
        }
        stream<<HeaderLine<<"\n";
        //保存数据
        for(int row = 0; row < datamodel->rowCount(); row++)
        {
            QString DataLine;
            for(int i = 0; i < colnum; i++)
            {
                DataLine += datamodel->item(row,i)->text();
                if(i != colnum-1)
                    DataLine += " ";
            }
            stream<<DataLine<<"\n";
        }
        HasSaved = true;
        QMessageBox::information(this, "Info", "保存成功！", QMessageBox::Ok, QMessageBox::Ok);
    }
    else
    {
        qInfo()<<"No need to save.";
        QMessageBox::information(this, "Info", "未修改信息，无需保存！", QMessageBox::Ok, QMessageBox::Ok);
    }
}

void Widget::on_AddButton_clicked()//“添加信息”按键
{
    //初始化新窗口
    InfoEditPage *newpage = new InfoEditPage(this);
    newpage->ui->ID_line->setPlaceholderText("请输入十位学号");
    newpage->ui->Name_line->setPlaceholderText("请输入姓名");
    newpage->ui->Dep_line->setPlaceholderText("请输入院系名称");
    newpage->ui->spinBox1->setValue(0);
    newpage->ui->spinBox2->setValue(0);
    newpage->ui->spinBox3->setValue(0);
    newpage->ui->Overallscore_line->setText("0");

    newpage->exec();
    if(newpage->getdata().size()!=0)
    {
        qInfo()<<"Adding...";
        QStringList Dataline = newpage->getdata();
        studentsdata.push_back(Student(Dataline));
        //在屏幕上显示
        QList<QStandardItem*> items;
        for(QString tmpdata : Dataline)
        {
            QStandardItem *tmpitem = new QStandardItem();
            tmpitem->setText(tmpdata);//设置文字
            tmpitem->setTextAlignment(Qt::AlignCenter);//居中对齐
            items.push_back(tmpitem);
        }
        datamodel->appendRow(items);
        ui->tableView->scrollToBottom();//翻到最后一行
        HasSaved = false;
    }
}

void Widget::on_SaveButton_clicked()//“保存修改”按键
{
    SaveData(filename);
}

void Widget::on_DeleteButton_clicked()//“删除信息”按键
{
    //弹出提示："确定要删除此学生？" Yes/No
    QMessageBox::StandardButton result = QMessageBox::question(this, "确认", "确定要删除此学生？", QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes);
    if(result == QMessageBox::Yes)//选择Yes，操作删除
    {
        QModelIndex index = ui->tableView->currentIndex();//获取选中位置的坐标
        int currow = index.row();//当前行位置
        qInfo()<<"Deleting row"<<currow+1<<"...";
        datamodel->removeRow(currow);//删除该行
        SavetoVector();//在QVector studentsdata中更新数据
        HasSaved = false;//修改为未保存状态
        QMessageBox::information(this, "Info", "删除成功！", QMessageBox::Ok, QMessageBox::Ok);
    }
    else{}//选择No，什么都不做
}

void Widget::on_EditButton_clicked()//“编辑信息”按键
{
    QModelIndex index = ui->tableView->currentIndex();//获取选中位置的坐标
    int currow = index.row();//当前行位置
    PasswordDialog *dialog = new PasswordDialog();
    dialog->exec();
    if(dialog->checkpass())
    {
        QString ID = datamodel->item(currow,0)->text();
        QString name = datamodel->item(currow,1)->text();
        QString dep = datamodel->item(currow,2)->text();
        int score1 = datamodel->item(currow,3)->text().toInt();
        int score2 = datamodel->item(currow,4)->text().toInt();
        int score3 = datamodel->item(currow,5)->text().toInt();
        QString finalscore = datamodel->item(currow,6)->text();

        //初始化窗口
        InfoEditPage *newpage = new InfoEditPage(this);
        newpage->ui->ID_line->setText(ID);
        newpage->ui->Name_line->setText(name);
        newpage->ui->Dep_line->setText(dep);
        newpage->ui->spinBox1->setValue(score1);
        newpage->ui->spinBox2->setValue(score2);
        newpage->ui->spinBox3->setValue(score3);
        newpage->ui->Overallscore_line->setText(finalscore);

        newpage->exec();
        if(newpage->getdata().size()!=0)
        {
            datamodel->removeRow(currow);
            //SavetoVector();
            qInfo()<<"Adding...";
            QStringList Dataline = newpage->getdata();//获取新修改的数据
            studentsdata[currow] = Student(Dataline);//在studentsdata缓存中修改
            //在屏幕上显示
            QList<QStandardItem*> items;
            for(QString tmpdata : Dataline)
            {
                QStandardItem *tmpitem = new QStandardItem();
                tmpitem->setText(tmpdata);//设置文字
                tmpitem->setTextAlignment(Qt::AlignCenter);//居中对齐
                items.push_back(tmpitem);
            }
            datamodel->insertRow(currow, items);//重新插入该行
            ui->tableView->scrollTo(index);//自动滚动到该行
            QMessageBox::information(this, "Info", "修改成功！", QMessageBox::Ok, QMessageBox::Ok);
            HasSaved = false;
        }
    }
}

void Widget::on_LessButton_clicked()//升序排序按键
{
    //先清除datamodel里的全部数据内容，保留表头
    int rowcnt = datamodel->rowCount();
    while(rowcnt--)
    {
        datamodel->removeRow(rowcnt);
    }
    //排序
    std::sort(studentsdata.begin(), studentsdata.end());
    //把studentsdata输出到屏幕上
    for(Student tmpstu : studentsdata)
    {
        QStringList Dataline = tmpstu.info;
        QList<QStandardItem*> items;
        for(QString tmpdata : Dataline)
        {
            QStandardItem *tmpitem = new QStandardItem();
            tmpitem->setText(tmpdata);//设置文字
            tmpitem->setTextAlignment(Qt::AlignCenter);//居中对齐
            items.push_back(tmpitem);
        }
        datamodel->appendRow(items);
    }
}

void Widget::on_GreaterButton_clicked()//降序排序按键
{
    //先清除datamodel里的全部数据内容，保留表头
    int rowcnt = datamodel->rowCount();
    while(rowcnt--)
    {
        datamodel->removeRow(rowcnt);
    }
    //排序
    std::sort(studentsdata.begin(), studentsdata.end(), studentcmp);
    for(Student tmpstu : studentsdata)
    {
        QStringList Dataline = tmpstu.info;
        QList<QStandardItem*> items;
        for(QString tmpdata : Dataline)
        {
            QStandardItem *tmpitem = new QStandardItem();
            tmpitem->setText(tmpdata);//设置文字
            tmpitem->setTextAlignment(Qt::AlignCenter);//居中对齐
            items.push_back(tmpitem);
        }
        datamodel->appendRow(items);
    }
}

//文件路径，需根据自己的电脑手动修改
QString Widget::filename = "C:\\Users\\ruanz\\Documents\\StudentManagement\\StudentInfo.txt";
