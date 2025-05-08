#ifndef SWITCH_H
#define SWITCH_H

#include <vector>

template <class T>
class MySwitch
{
private:
    // 存储Case信息的结构体
    struct Case
    {
        T flag;
        void (*op)(int &);
        int *target;
        bool shouldBreak;

        Case(T f, void (*o)(int &), int *t, bool sb)
            : flag(f), op(o), target(t), shouldBreak(sb) {}
    };

    // 存储所有Case
    std::vector<Case> cases;

public:
    // 添加一个Case
    void addCase(T flag, void (*op)(int &), int *target, bool shouldBreak)
    {
        cases.emplace_back(flag, op, target, shouldBreak);
    }

    // 执行匹配的Case
    void execute(T value)
    {
        for (const auto &c : cases)
        {
            if (value == c.flag)
            {
                c.op(*(c.target));
                if (c.shouldBreak)
                    break;
            }
        }
    }
};

#endif // SWITCH_H
