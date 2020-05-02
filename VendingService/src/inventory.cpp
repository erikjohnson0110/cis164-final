#include <QJsonArray>
#include "inventory.h"

Inventory::Inventory(){
}
Inventory::~Inventory(){
}

// Gets an item by its vend code.  Returns nullptr if not found.
InventoryItem* Inventory::getInventoryItemByVendCode(string vc){
    InventoryItem* returnVal;
    try
    {
        returnVal = this->items.at(vc);
    }
    catch (const std::out_of_range& oor)
    {
        returnVal = nullptr;
    }
    return returnVal;
}

bool Inventory::addInventoryItem(string vc, InventoryItem &ii){
    bool returnVal = false;
    try
    {
        this->items.at(vc);
    }
    catch (const std::out_of_range& oor)
    {
        this->items[vc] = &ii;
        returnVal = true;
    }
    return returnVal;
}

bool Inventory::removeItem(string vc){
    int itemsRemoved = this->items.erase(vc);

    if (itemsRemoved > 0){
        return true;
    }
    else{
        return false;
    }
}

void Inventory::writeJson(QJsonObject &json) const
{
    QJsonArray allItems;
    for (pair<string, InventoryItem*> i : this->items){
        QJsonObject jsonObj;
        InventoryItem *pt = i.second;
        pt->writeJson(jsonObj);
        allItems.append(jsonObj);
    }
    json["inventory"] = allItems;
}
