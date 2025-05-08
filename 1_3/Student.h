#ifndef STUDENT_H
#define STUDENT_H

#include <string>
using namespace std;

class Student
{
private:
    string name;
    int presenttimes;
    int absenttimes;

public:
    Student(string name);
    ~Student();
    string getName();
    int getPresentTimes();
    int getAbsentTimes();
    void incrementPresentTimes();
    void incrementAbsentTimes();
    void decrementAbsentTimes();
};

#endif // STUDENT_H