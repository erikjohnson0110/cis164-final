#ifndef COMPANY_H
#define COMPANY_H
#include <map>
#include "vendingmachine.h"

using namespace std;

class Company
{
private:
    string companyName;
    map<int, VendingMachine*> machines;

public:
    string getCompanyName();
    void setCompanyName(string cn);

    bool addMachine(int mid, VendingMachine &m);
    bool removeMachine(int mid);
    VendingMachine* findMachineById(int mid);
    VendingMachine* findMachineByLocation(string loc);
    map<int, VendingMachine*> getAllMachines();
};

#endif // COMPANY_H
