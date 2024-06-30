#ifndef STUDENT_H
#define STUDENT_H

#include <QStringList>

class Student
{
private:
    QStringList info;
public:
    Student(QStringList &list);
    ~Student(){};
    bool operator<(const Student &obj);

    friend class Widget;
    friend bool studentcmp(const Student obj1, const Student obj2);
};

bool studentcmp(const Student obj1, const Student obj2);

#endif // STUDENT_H
