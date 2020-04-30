#include <QJsonArray>
#include "inventory.h"

Inventory::Inventory(){
}
Inventory::~Inventory(){
}

// Gets an item by its vend code.  Returns nullptr if not found.
Item* Inventory::getItemByVendCode(string vc){
    Item* returnVal;

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

bool Inventory::addItem(string vc, Item &item){
    bool returnVal = false;
    try
    {
        this->items.at(vc);
    }
    catch (const std::out_of_range& oor)
    {
        this->items[vc] = &item;
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

void Inventory::readJson(const QJsonObject &json)
{

}
void Inventory::writeJson(QJsonObject &json) const
{
    QJsonArray allItems;
    for (pair<string, Item*> i : this->items){
        QJsonObject jsonObj;
        i.second->writeJson(jsonObj);
        allItems.append(jsonObj);
    }
    json["inventory"] = allItems;
}
