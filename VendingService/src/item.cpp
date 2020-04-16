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
