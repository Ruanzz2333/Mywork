#include "student.h"

Student::Student(QStringList &list): info(list){};

bool Student::operator<(const Student &obj)
{
    int val = info[6].toInt();
    int objval = obj.info[6].toInt();
    return val < objval;
}

bool studentcmp(const Student obj1, const Student obj2)
{
    int val = obj1.info[6].toInt();
    int objval = obj2.info[6].toInt();
    return val > objval;
}
