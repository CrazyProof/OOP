#pragma once
#include "Robot.h"

class Bob : public Robot
{
public:
    Bob() = delete;
    Bob(int partnum);
    ~Bob() override;
    void add_part(Part) override;
    bool is_full() override;
    int run() override;
    std::ostream &print(std::ostream &os) const override;
};