#include "Factor.h"
#include <iostream>
#include <algorithm>

// 手动实现 gcd 函数
int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

Factor::Factor(int num, int den) : numerator(num), denominator(den)
{
    if (denominator == 0)
    {
        numerator = 0;
        denominator = 0; // 非法分数
    }
    else
    {
        simplify();
    }
}

void Factor::simplify()
{
    if (numerator == 0)
    {
        denominator = 1;
        return;
    }
    int gcdValue = gcd(numerator, denominator);
    numerator /= gcdValue;
    denominator /= gcdValue;
    if (denominator < 0)
    { // 确保分母为正
        numerator = -numerator;
        denominator = -denominator;
    }
}

std::istream &operator>>(std::istream &in, Factor &f)
{
    char slash;
    in >> f.numerator >> slash >> f.denominator;
    if (slash != '/' || f.denominator == 0)
    { // 检查输入格式和非法分母
        f.numerator = 0;
        f.denominator = 0; // 非法分数
    }
    else
    {
        f.simplify();
    }
    return in;
}

std::ostream &operator<<(std::ostream &out, const Factor &f)
{
    if (f.numerator == 0 && f.denominator == 0)
    {
        out << "nan";
    }
    else if (f.denominator == 0)
    {
        out << "nan";
    }
    else
    {
        out << f.numerator << '/' << f.denominator;
    }
    return out;
}

Factor Factor::operator+(const Factor &other) const
{
    int num = numerator * other.denominator + other.numerator * denominator;
    int den = denominator * other.denominator;
    return Factor(num, den);
}

Factor Factor::operator*(const Factor &other) const
{
    int num = numerator * other.numerator;
    int den = denominator * other.denominator;
    return Factor(num, den);
}

Factor Factor::operator/(const Factor &other) const
{
    if (other.numerator == 0)
    {
        return Factor(0, 0); // 非法分数
    }
    int num = numerator * other.denominator;
    int den = denominator * other.numerator;
    return Factor(num, den);
}

bool Factor::operator<(const Factor &other) const
{
    return static_cast<long long>(numerator) * other.denominator <
           static_cast<long long>(other.numerator) * denominator;
}

bool Factor::operator>(const Factor &other) const
{
    return static_cast<long long>(numerator) * other.denominator >
           static_cast<long long>(other.numerator) * denominator;
}

bool Factor::operator==(const Factor &other) const
{
    return static_cast<long long>(numerator) * other.denominator ==
           static_cast<long long>(other.numerator) * denominator;
}