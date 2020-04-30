#ifndef INVENTORY_H
#define INVENTORY_H
#include <map>
#include <memory>
#include "item.h"

using namespace std;

class Inventory
{
private:
    map<string, Item*> items;
public:
    Inventory();
    ~Inventory();
    Item* getItemByVendCode(string vc);
    bool addItem(string vc, Item &item);
    bool removeItem(string vc);

    void readJson(const QJsonObject &json);
    void writeJson(QJsonObject &json) const;
};

#endif // INVENTORY_H
