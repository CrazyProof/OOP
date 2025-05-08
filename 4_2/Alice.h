#pragma once
#include "Robot.h"

class Alice : public Robot
{
public:
    Alice() = delete;
    Alice(int partnum);
    ~Alice() override;
    void add_part(Part) override;
    bool is_full() override;
    int run() override;
    std::ostream &print(std::ostream &os) const override;
};