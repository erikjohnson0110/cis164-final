#include "item.h"

Item::Item(){
}

Item::Item(string n, double p, double s, string su){
    this->name = n;
    this->price = p;
    this->size = s;
    this->sizeUnits = su;
}

Item::~Item(){
}

string Item::getName(){
    return this->name;
}

void Item::setName(string n){
    this->name = n;
}

double Item::getPrice(){
    return this->price;
}

void Item::setPrice(double p){
    this->price = p;
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

    // price
    if (json.contains("price") && json["price"].isDouble()){
        this->setPrice(json["price"].toDouble());
    }
    else{
        this->setPrice(0.0);
    }

    // size
    if (json.contains("size") && json["size"].isDouble()){
        this->setSize(json["size"].toDouble());
    }
    else{
        this->setSize(0.0);
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
    json["price"] = this->price;
    json["size"] =  this->size;
    json["sizeUnits"] =  QString::fromStdString(this->sizeUnits);
}
