#include "Student.h"
#include <string>

Student::Student(string name)
{
    this->name = name;
    presenttimes = 0;
    absenttimes = 0;
}

Student::~Student() {}

string Student::getName()
{
    return name;
}

int Student::getPresentTimes()
{
    return presenttimes;
}

int Student::getAbsentTimes()
{
    return absenttimes;
}

void Student::incrementPresentTimes()
{
    presenttimes++;
}

void Student::incrementAbsentTimes()
{
    absenttimes++;
}

void Student::decrementAbsentTimes()
{
    if (absenttimes > 0)
    {
        absenttimes--;
    }
}