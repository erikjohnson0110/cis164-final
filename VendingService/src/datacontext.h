#ifndef DATACONTEXT_H
#define DATACONTEXT_H
#include <map>
#include "company.h"
#include "inventoryitem.h"

using namespace std;

// I am not implementing a Database for this project, so the DataContext class will
// encapsulate all of the program's data.
class DataContext
{
private:
    map<string, Company*> companies;
    InventoryItem* createMountainDew(int, int);
    InventoryItem* createBottledWater(int, int);
    InventoryItem* createSlimJim(int, int);
    InventoryItem* createEggSaladSandwich(int, int);
public:
    DataContext();
    ~DataContext();

    bool addCompany(string cn, Company &comp);
    bool removeCompany(string cn);
    Company* getCompanyByName(string cn);
};

#endif // DATACONTEXT_H
