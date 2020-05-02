#include "inventoryitem.h"

InventoryItem::InventoryItem(){
    this->item = nullptr;
    this->quantity = 0;
    this->maxQuantity = 0;
}

InventoryItem::InventoryItem(Item &i, int q, int mq){
    this->item = &i;
    this->quantity = q;
    this->maxQuantity = mq;
}

InventoryItem::~InventoryItem(){
}

Item* InventoryItem::getItem(){
    return this->item;
}
void InventoryItem::setItem(Item &i){
    this->item = &i;
}

int InventoryItem::getQuantity(){
    return this->quantity;
}
void InventoryItem::setQuantity(int q){
    this->quantity = q;
}

int InventoryItem::getMaxQuantity(){
    return this->maxQuantity;
}
void InventoryItem::setMaxQuantity(int mq){
    this->maxQuantity = mq;
}

bool InventoryItem::sellItem(){
    if (this->quantity > 0){
        this->quantity--;
        return true;
    }
    else{
        return false;
    }
}

void InventoryItem::readJson(const QJsonObject &json){
    // item
    if (json.contains("item") && json["item"].isObject()){
        this->item = new Item();
        this->item->readJson(json["item"].toObject());
    }

    //quantity
    if (json.contains("quantity") && json["quantity"].isDouble()){
        this->quantity = json["quantity"].toInt();
    }

    //maxquantity
    if (json.contains("maxQuantity") && json["maxQuantity"].isDouble()){
        this->maxQuantity = json["maxQuantity"].toInt();
    }

}
void InventoryItem::writeJson(QJsonObject &json) const{
    QJsonObject itemJsonObj;
    this->item->writeJson(itemJsonObj);
    json["item"] = itemJsonObj;
    json["quantity"] = this->quantity;
    json["maxQuantity"] = this->maxQuantity;
}
