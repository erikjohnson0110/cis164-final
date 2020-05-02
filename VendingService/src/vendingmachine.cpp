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

void VendingMachine::setTotalSales(double s){
    this->totalSales = s;
}

double VendingMachine::getTotalSales(){
    return this->totalSales;
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

void VendingMachine::readJson(const QJsonObject &json)
{
    //int id;
    if (json.contains("id") && json["id"].isDouble()){
            this->setId(json["id"].toInt());
    }
    else
    {
        this->setId(0);
    }

    //bool active;
    if (json.contains("active") && json["active"].isBool()){
        if (json["active"].toBool())
        {
            this->activate();
        }
        else
        {
            this->deactivate();
        }
    }
    else
    {
        this->deactivate();
    }

    //string location;
    if (json.contains("location") && json["location"].isString()){
        this->setLocation(json["location"].toString().toStdString());
    }
    else
    {
        this->setLocation(nullptr);
    }

    // double totalSales
    if (json.contains("totalSales") && json["totalSales"].isDouble()){
        this->setTotalSales(json["totalSales"].toDouble());
    }
    else{
        this->setTotalSales(0.0);
    }

    //MachineModel model;
    if (json.contains("model") && json["model"].isString()){
        // TODO
    }
    //Inventory inventory;
        // TODO
}

void VendingMachine::writeJson(QJsonObject &json) const
{
    json["id"] =  this->id;
    json["active"] =  this->active;
    json["location"] =  QString::fromStdString(this->location);
    json["totalSales"] = this->totalSales;
    json["model"] =  QString::fromStdString(machineModelNames[(int)this->model]);
    this->inventory.writeJson(json);
}
