#include "item.h"

Item::Item(){
}

Item::Item(string n, int q, double s, string su){
    this->name = n;
    this->quantity = q;
    this->size = s;
    this->sizeUnits = su;
}

Item::~Item(){
}

int Item::getQuantity(){
    return this->quantity;
}
void Item::setQuantity(int q){
    this->quantity = q;
}


string Item::getName(){
    return this->name;
}

void Item::setName(string n){
    this->name = n;
}

double Item::getSize(){
    return this->size;
}
void Item::setSize(double s){
    this->size = s;
}

string Item::getSizeUnits(){
    return this->sizeUnits;
}
void Item::setSizeUnits(string su){
    this->sizeUnits = su;
}

void Item::readJson(const QJsonObject &json){
    // name
    if (json.contains("name") && json["name"].isString()){
            this->setName(json["name"].toString().toStdString());
    }
    else
    {
        this->setName(nullptr);
    }

    // quantity
    if (json.contains("quantity") && json["quantity"].isDouble()){
        this->setQuantity(json["quantity"].toInt());
    }
    else{
        this->setQuantity(0);
    }

    // size
    if (json.contains("size") && json["size"].isDouble()){
        this->setQuantity(json["size"].toDouble());
    }
    else{
        this->setQuantity(0.0);
    }

    // sizeUnits
    if (json.contains("sizeUnits") && json["sizeUnits"].isString()){
            this->setSizeUnits(json["sizeUnits"].toString().toStdString());
    }
    else
    {
        this->setSizeUnits(nullptr);
    }
}
void Item::writeJson(QJsonObject &json) const{
    json["name"] =  QString::fromStdString(this->name);
    json["quantity"] =  this->quantity;
    json["size"] =  this->size;
    json["sizeUnits"] =  QString::fromStdString(this->sizeUnits);
}
