#ifndef FACTOR_H
#define FACTOR_H

#include <iostream>

class Factor
{
private:
    int numerator;   // 分子
    int denominator; // 分母

    void simplify(); // 化简分数

public:
    Factor(int num = 0, int den = 1); // 构造函数

    // 输入输出运算符重载
    friend std::istream &operator>>(std::istream &in, Factor &f);
    friend std::ostream &operator<<(std::ostream &out, const Factor &f);

    // 算术运算符重载
    Factor operator+(const Factor &other) const;
    Factor operator*(const Factor &other) const;
    Factor operator/(const Factor &other) const;

    // 比较运算符重载
    bool operator<(const Factor &other) const;
    bool operator>(const Factor &other) const;
    bool operator==(const Factor &other) const;
};

#endif // FACTOR_H