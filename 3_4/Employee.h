#pragma once
#include "_Employee.h"
#include "Device.h"
#include <string>
#include <vector>
#include <iostream>

// 安全配置文件具体实现
class MDRSecurityProfile : public SecurityProfile
{
public:
    MDRSecurityProfile(int level);
    bool validate(Device *d) override;
    void upgradeLevel() override;
    SecurityProfile *clone() override;
};

class OnDSecurityProfile : public SecurityProfile
{
public:
    OnDSecurityProfile(int level);
    bool validate(Device *d) override;
    void upgradeLevel() override;
    SecurityProfile *clone() override;
};

// 员工具体实现
class MDRJunior : public Employee
{
public:
    MDRJunior(int id);
    Employee *promote() override;
    bool accessDevice(Device *d) override;
    std::string getType() const override;
    Department getDepartment() const override;
    Employee *clone() override;
};

class MDRSenior : public Employee
{
public:
    MDRSenior(int id);
    Employee *promote() override;
    bool accessDevice(Device *d) override;
    std::string getType() const override;
    Department getDepartment() const override;
    Employee *clone() override;
};

class OnDJunior : public Employee
{
public:
    OnDJunior(int id);
    Employee *promote() override;
    bool accessDevice(Device *d) override;
    std::string getType() const override;
    Department getDepartment() const override;
    Employee *clone() override;
};

class OnDSenior : public Employee
{
public:
    OnDSenior(int id);
    Employee *promote() override;
    bool accessDevice(Device *d) override;
    std::string getType() const override;
    Department getDepartment() const override;
    Employee *clone() override;
};
