#ifndef INVENTORYITEM_H
#define INVENTORYITEM_H
#include "item.h"

class InventoryItem
{
private:
    Item *item;
    int quantity;
    int maxQuantity;

public:
    InventoryItem();
    InventoryItem(Item &i, int, int);
    ~InventoryItem();

    Item* getItem();
    void setItem(Item &i);

    int getQuantity();
    void setQuantity(int);

    int getMaxQuantity();
    void setMaxQuantity(int);

    bool sellItem();

    void readJson(const QJsonObject &json);
    void writeJson(QJsonObject &json) const;
};

#endif // INVENTORYITEM_H
