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

    }
    return returnVal;
}

void Inventory::addItem(string vc, Item &item){
    //this->items.insert(std::pair<string, Item*>(vc,item));
    this->items[vc] = &item;

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
