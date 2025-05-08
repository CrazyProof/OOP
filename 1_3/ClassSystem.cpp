#include "ClassSystem.h"
#include "Student.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

ClassSystem::ClassSystem() : totalClasses(0) {}

ClassSystem::~ClassSystem()
{
}

void ClassSystem::addStudent(Student stu)
{
    stus.push_back(stu);
}

void ClassSystem::addClassNumber()
{
    totalClasses++;
    // 缺勤次数等于总课时数减去出勤次数
    for (auto &stu : stus)
    {
        stu.incrementAbsentTimes();
    }
}

void ClassSystem::signIn(string name)
{
    auto it = find_if(stus.begin(), stus.end(), [&name](Student &stu)
                      { return stu.getName() == name; });
    if (it != stus.end())
    {
        it->incrementPresentTimes();
        // 签到后减少一次缺勤
        it->decrementAbsentTimes();
    }
}

Student ClassSystem::getStudentById(int i)
{
    return stus[i];
}

Student ClassSystem::getStudentByName(string name)
{
    auto it = find_if(stus.begin(), stus.end(), [&name](Student &stu)
                      { return stu.getName() == name; });
    return (it != stus.end()) ? *it : Student("");
}