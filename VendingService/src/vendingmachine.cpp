#include "vendingmachine.h"

// CONSTRUCTORS AND DESTRUCTORS
VendingMachine::VendingMachine(){

}

VendingMachine::VendingMachine(int id, string loc, MachineModel mmod)
{
    this->setId(id);
    this->setLocation(loc);
    this->setModel(mmod);
}

VendingMachine::~VendingMachine(){

}

// GETTERS AND SETTERS
void VendingMachine::setId(int id){
    this->id = id;
}
int VendingMachine::getId(){
    return this->id;
}

bool VendingMachine::isActive(){
    return this->active;
}
void VendingMachine::activate(){
    if (!this->active){
        this->active = true;
    }
    else
    {
        // error already active
    }
}
void VendingMachine::deactivate(){
    if (this->active){
        this->active = false;
    }
    else
    {
        // error already deactivated
    }

}

void VendingMachine::setLocation(string loc)
{
    this->location = loc;
}
string VendingMachine::getLocation()
{
    return this->location;
}

void VendingMachine::setModel(MachineModel mod)
{
    this->model = mod;
}
MachineModel VendingMachine::getModel()
{
    return this->model;
}

Item* VendingMachine::getItemByVendCode(string vc)
{
    return this->inventory.getItemByVendCode(vc);
}
bool VendingMachine::addItem(string vc, Item &item)
{
    return this->inventory.addItem(vc, item);
}
bool VendingMachine::removeItem(string vc)
{
    return this->inventory.removeItem(vc);
}
