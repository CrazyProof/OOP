#include <iostream>
using namespace std;

class Base
{
public:
    virtual void print()
    {
        cout << "Base class" << endl;
    }
};

class Derived : public Base
{
public:
    void print() override
    {
        cout << "Derived class" << endl;
    }
};

int main()
{
    Base *base = new Base();
    Derived *derived = new Derived();

    Base *bp = static_cast<Base *>(derived);
    Derived *dp = static_cast<Derived *>(base);

    bp->print();
    dp->print();

    delete base;
    delete derived;

    return 0;
}
