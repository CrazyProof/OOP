#include <iostream>
using namespace std;

class Base
{
public:
    virtual void show() { cout << "Base show()" << endl; }
    void print() { cout << "Base print()" << endl; }
};

class Derived : public Base
{
public:
    void show() override { cout << "Derived show()" << endl; }
    void print() { cout << "Derived print()" << endl; }
};

int main()
{
    Base *b = new Derived();
    b->show();
    b->print();
    delete b;
    return 0;
}
