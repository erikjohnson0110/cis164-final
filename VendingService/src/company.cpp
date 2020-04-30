#include "company.h"

string Company::getCompanyName()
{
    return this->companyName;
}
void Company::setCompanyName(string n)
{
    this->companyName = n;
}

bool Company::addMachine(int mid, VendingMachine &m)
{
    bool returnVal = false;
    try
    {
        this->machines.at(mid);
    }
    catch (const std::out_of_range& oor)
    {
        this->machines[mid] = &m;
        returnVal = true;
    }
    return returnVal;
}
bool Company::removeMachine(int mid)
{
    int machinesRemoved = this->machines.erase(mid);

    if (machinesRemoved > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

VendingMachine* Company::findMachineById(int mid)
{
    VendingMachine* returnVal;

    try
    {
        returnVal = this->machines.at(mid);
    }
    catch (const std::out_of_range& oor)
    {
        returnVal = nullptr;
    }
    return returnVal;

}

VendingMachine* Company::findMachineByLocation(string loc)
{
    VendingMachine* returnVal = nullptr;
    for (pair<int, VendingMachine*> vm : this->machines)
    {
        if (vm.second->getLocation().compare(loc) == 0)
        {
            return vm.second;
        }
    }
    return returnVal;
}

map<int, VendingMachine*> Company::getAllMachines()
{
    return this->machines;
}
