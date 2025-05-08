#ifndef CLASSSYSTEM_H
#define CLASSSYSTEM_H

#include "Student.h"
#include <vector>
#include <string>
using namespace std;

class ClassSystem
{
private:
    vector<Student> stus;
    int totalClasses;

public:
    ClassSystem();
    ~ClassSystem();
    void addStudent(Student stu);
    void addClassNumber();
    void signIn(string name);
    Student getStudentById(int i);
    Student getStudentByName(string name);
};

#endif // CLASSSYSTEM_H