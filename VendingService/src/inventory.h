#ifndef INVENTORY_H
#define INVENTORY_H
#include <map>
#include <memory>
#include "inventoryitem.h"

using namespace std;

class Inventory
{
private:
    map<string, InventoryItem*> items;
public:
    Inventory();
    ~Inventory();
    InventoryItem* getInventoryItemByVendCode(string vc);
    bool addInventoryItem(string vc, InventoryItem &ii);
    bool removeItem(string vc);

    void readJson(const QJsonObject &json);
    void writeJson(QJsonObject &json) const;
};

#endif // INVENTORY_H
