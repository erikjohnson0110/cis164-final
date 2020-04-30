#ifndef VENDINGMACHINE_H
#define VENDINGMACHINE_H
#include "inventory.h"
#include "enums.h"

using namespace std;

class VendingMachine
{
private:
    int id;
    bool active;
    string location;
    MachineModel model;
    Inventory inventory;

public:
    VendingMachine();
    VendingMachine(int, string, MachineModel);
    ~VendingMachine();

    void setId(int);
    int getId();

    bool isActive();
    void activate();
    void deactivate();

    void setLocation(string);
    string getLocation();

    void setModel(MachineModel);
    MachineModel getModel();

    Item* getItemByVendCode(string vc);
    bool addItem(string vc, Item &item);
    bool removeItem(string vc);

    void readJson(const QJsonObject &json);
    void writeJson(QJsonObject &json) const;
};

#endif // VENDINGMACHINE_H
