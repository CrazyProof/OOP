#include "Employee.h"
#include "Device.h"

// Employee 基类实现
Employee::Employee(int id) : id(id) {}

Employee::~Employee()
{
    delete profile;
}

// MDR安全配置文件实现
MDRSecurityProfile::MDRSecurityProfile(int level)
{
    this->level = level;
    this->department = MACRODATA_REFINEMENT;
}

bool MDRSecurityProfile::validate(Device *d)
{
    // 检查部门权限
    if (d->getAllowedDepartment() != MACRODATA_REFINEMENT)
    {
        return false;
    }

    // 检查安全等级
    if (level < 2 && (dynamic_cast<DataTerminal *>(d) != nullptr))
    {
        return false;
    }

    // 检查设备依赖
    if (!d->isUnlocked(accessed))
    {
        return false;
    }

    return true;
}

void MDRSecurityProfile::upgradeLevel()
{
    level = 2;
}

SecurityProfile *MDRSecurityProfile::clone()
{
    MDRSecurityProfile *newProfile = new MDRSecurityProfile(level);
    newProfile->accessed = accessed;
    return newProfile;
}

// O&D安全配置文件实现
OnDSecurityProfile::OnDSecurityProfile(int level)
{
    this->level = level;
    this->department = OPTICS_AND_DESIGN;
}

bool OnDSecurityProfile::validate(Device *d)
{
    // 光学部初级成员不能访问任何设备
    if (level < 2)
    {
        return false;
    }

    // 检查部门权限
    if (d->getAllowedDepartment() != OPTICS_AND_DESIGN)
    {
        return false;
    }

    // 检查设备依赖
    if (!d->isUnlocked(accessed))
    {
        return false;
    }

    return true;
}

void OnDSecurityProfile::upgradeLevel()
{
    level = 2;
}

SecurityProfile *OnDSecurityProfile::clone()
{
    OnDSecurityProfile *newProfile = new OnDSecurityProfile(level);
    newProfile->accessed = accessed;
    return newProfile;
}

// MDR初级员工实现
MDRJunior::MDRJunior(int id) : Employee(id)
{
    profile = new MDRSecurityProfile(1);
}

Employee *MDRJunior::promote()
{
    MDRSenior *senior = new MDRSenior(id);
    delete senior->profile;             // 删除默认创建的profile
    senior->profile = profile->clone(); // 复制当前profile到新对象
    senior->profile->upgradeLevel();    // 提升安全等级
    profile = nullptr;                  // 防止析构函数重复删除
    return senior;
}

bool MDRJunior::accessDevice(Device *d)
{
    // 检查部门权限
    if (d->getAllowedDepartment() != MACRODATA_REFINEMENT)
    {
        std::cout << "No permission. ACCESS DENIED." << std::endl;
        return false;
    }

    // 检查安全等级
    if (dynamic_cast<DataTerminal *>(d) != nullptr)
    {
        std::cout << "No permission. ACCESS DENIED." << std::endl;
        return false;
    }

    // 检查设备依赖
    if (!d->isUnlocked(profile->accessed))
    {
        std::cout << "Dependency not met. ACCESS DENIED." << std::endl;
        return false;
    }

    // 通过所有检查，执行设备操作
    d->execute();
    profile->accessed.push_back(d);
    return true;
}

std::string MDRJunior::getType() const
{
    return "MDR-Junior";
}

Department MDRJunior::getDepartment() const
{
    return MACRODATA_REFINEMENT;
}

Employee *MDRJunior::clone()
{
    MDRJunior *newEmp = new MDRJunior(id);
    delete newEmp->profile;
    newEmp->profile = profile->clone();
    return newEmp;
}

// MDR高级员工实现
MDRSenior::MDRSenior(int id) : Employee(id)
{
    profile = new MDRSecurityProfile(2);
}

Employee *MDRSenior::promote()
{
    return this; // 已经是最高级别，返回自己
}

bool MDRSenior::accessDevice(Device *d)
{
    // 检查部门权限
    if (d->getAllowedDepartment() != MACRODATA_REFINEMENT)
    {
        std::cout << "No permission. ACCESS DENIED." << std::endl;
        return false;
    }

    // 检查设备依赖
    if (!d->isUnlocked(profile->accessed))
    {
        std::cout << "Dependency not met. ACCESS DENIED." << std::endl;
        return false;
    }

    // 通过所有检查，执行设备操作
    d->execute();
    profile->accessed.push_back(d);
    return true;
}

std::string MDRSenior::getType() const
{
    return "MDR-Senior";
}

Department MDRSenior::getDepartment() const
{
    return MACRODATA_REFINEMENT;
}

Employee *MDRSenior::clone()
{
    MDRSenior *newEmp = new MDRSenior(id);
    delete newEmp->profile;
    newEmp->profile = profile->clone();
    return newEmp;
}

// O&D初级员工实现
OnDJunior::OnDJunior(int id) : Employee(id)
{
    profile = new OnDSecurityProfile(1);
}

Employee *OnDJunior::promote()
{
    OnDSenior *senior = new OnDSenior(id);
    delete senior->profile;
    senior->profile = profile->clone();
    senior->profile->upgradeLevel();
    profile = nullptr;
    return senior;
}

bool OnDJunior::accessDevice(Device *d)
{
    // 初级光学部员工不能访问任何设备
    std::cout << "No permission. ACCESS DENIED." << std::endl;
    return false;
}

std::string OnDJunior::getType() const
{
    return "O&D-Junior";
}

Department OnDJunior::getDepartment() const
{
    return OPTICS_AND_DESIGN;
}

Employee *OnDJunior::clone()
{
    OnDJunior *newEmp = new OnDJunior(id);
    delete newEmp->profile;
    newEmp->profile = profile->clone();
    return newEmp;
}

// O&D高级员工实现
OnDSenior::OnDSenior(int id) : Employee(id)
{
    profile = new OnDSecurityProfile(2);
}

Employee *OnDSenior::promote()
{
    return this; // 已经是最高级别，返回自己
}

bool OnDSenior::accessDevice(Device *d)
{
    // 检查部门权限
    if (d->getAllowedDepartment() != OPTICS_AND_DESIGN)
    {
        std::cout << "No permission. ACCESS DENIED." << std::endl;
        return false;
    }

    // 检查设备依赖
    if (!d->isUnlocked(profile->accessed))
    {
        std::cout << "Dependency not met. ACCESS DENIED." << std::endl;
        return false;
    }

    // 通过所有检查，执行设备操作
    d->execute();
    profile->accessed.push_back(d);
    return true;
}

std::string OnDSenior::getType() const
{
    return "O&D-Senior";
}

Department OnDSenior::getDepartment() const
{
    return OPTICS_AND_DESIGN;
}

Employee *OnDSenior::clone()
{
    OnDSenior *newEmp = new OnDSenior(id);
    delete newEmp->profile;
    newEmp->profile = profile->clone();
    return newEmp;
}
