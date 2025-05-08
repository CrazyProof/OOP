#include "Device.h"

// BaseLock 实现
bool BaseLock::isUnlocked(const std::vector<Device *> &accessed)
{
    return true; // BaseLock 没有依赖，总是可以解锁
}

void BaseLock::execute()
{
    std::cout << "BaseLock engaged." << std::endl;
}

std::string BaseLock::getName() const
{
    return "BaseLock";
}

Department BaseLock::getAllowedDepartment() const
{
    return MACRODATA_REFINEMENT; // BaseLock 允许 MDR 部门访问
}

// SecurityPanel 实现
bool SecurityPanel::isUnlocked(const std::vector<Device *> &accessed)
{
    // 检查是否已访问过 BaseLock
    for (auto *device : accessed)
    {
        if (dynamic_cast<BaseLock *>(device))
        {
            return true;
        }
    }
    return false;
}

void SecurityPanel::execute()
{
    std::cout << "SecurityPanel activated." << std::endl;
}

std::string SecurityPanel::getName() const
{
    return "SecurityPanel";
}

Department SecurityPanel::getAllowedDepartment() const
{
    return MACRODATA_REFINEMENT; // SecurityPanel 允许 MDR 部门访问
}

// DataTerminal 实现
DataTerminal::DataTerminal(int capacity) : capacity(capacity) {}

bool DataTerminal::isUnlocked(const std::vector<Device *> &accessed)
{
    // 检查是否已访问过 SecurityPanel
    for (auto *device : accessed)
    {
        if (dynamic_cast<SecurityPanel *>(device))
        {
            return true;
        }
    }
    return false;
}

void DataTerminal::execute()
{
    std::cout << "Processed " << capacity << "TB data." << std::endl;
}

std::string DataTerminal::getName() const
{
    return "DataTerminal";
}

Department DataTerminal::getAllowedDepartment() const
{
    return MACRODATA_REFINEMENT; // DataTerminal 允许 MDR 部门访问
}

// OpticalTool 实现
bool OpticalTool::isUnlocked(const std::vector<Device *> &accessed)
{
    return true; // OpticalTool 没有依赖，总是可以解锁
}

void OpticalTool::execute()
{
    std::cout << "OpticalTool adjusted." << std::endl;
}

std::string OpticalTool::getName() const
{
    return "OpticalTool";
}

Department OpticalTool::getAllowedDepartment() const
{
    return OPTICS_AND_DESIGN; // OpticalTool 只允许 O&D 部门访问
}
