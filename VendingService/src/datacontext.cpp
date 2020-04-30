#include <memory>
#include "datacontext.h"
#include "enums.h"

// I am not using a database for this project.  This constructor will
// initialize all program data.
DataContext::DataContext()
{
    // create company, create machines, setup machines, add machines.
    Company *corpOne = new Company();
    corpOne->setCompanyName("Mego-Corp");
    VendingMachine *mcMachineOne = new VendingMachine(1, "123 Main St", MachineModel::TK421);
    VendingMachine *mcMachineTwo = new VendingMachine(2, "2000 64th Ave", MachineModel::VM4000);
    VendingMachine *mcMachineThree = new VendingMachine(3, "475 Fake Blvd", MachineModel::VM4000);

    mcMachineOne->addItem("A1", *createMountainDew());
    mcMachineOne->addItem("A2", *createMountainDew());
    mcMachineOne->addItem("A3", *createBottledWater());
    mcMachineOne->addItem("A4", *createBottledWater());

    mcMachineTwo->addItem("A1", *createSlimJim());
    mcMachineTwo->addItem("A2", *createEggSaladSandwich());

    mcMachineThree->addItem("A1", *createSlimJim());
    mcMachineThree->addItem("A2", *createEggSaladSandwich());
    mcMachineThree->addItem("A3", *createEggSaladSandwich());
    mcMachineThree->addItem("A4", *createEggSaladSandwich());


    corpOne->addMachine(mcMachineOne->getId(), *mcMachineOne);
    corpOne->addMachine(mcMachineTwo->getId(), *mcMachineTwo);
    corpOne->addMachine(mcMachineThree->getId(), *mcMachineThree);

    // create company, create machines, setup machines, add machines.
    Company *corpTwo = new Company();
    corpTwo->setCompanyName("OfficeVend");
    VendingMachine *ovMachineOne = new VendingMachine(1, "200 Maple St", MachineModel::TK421);
    VendingMachine *ovMachineTwo = new VendingMachine(2, "303 2nd St", MachineModel::FoodBoxXD);
    VendingMachine *ovMachineThree = new VendingMachine(3, "1020 Quiet Ln", MachineModel::Vendtron20);

    ovMachineOne->addItem("A1", *createMountainDew());
    ovMachineOne->addItem("A2", *createMountainDew());
    ovMachineOne->addItem("A3", *createBottledWater());

    ovMachineTwo->addItem("A1", *createSlimJim());
    ovMachineTwo->addItem("A2", *createEggSaladSandwich());
    ovMachineTwo->addItem("A3", *createEggSaladSandwich());
    ovMachineTwo->addItem("A4", *createEggSaladSandwich());

    ovMachineThree->addItem("A1", *createSlimJim());
    ovMachineThree->addItem("A2", *createEggSaladSandwich());
    ovMachineThree->addItem("A3", *createMountainDew());
    ovMachineThree->addItem("A4", *createBottledWater());

    corpTwo->addMachine(ovMachineOne->getId(), *ovMachineOne);
    corpTwo->addMachine(ovMachineTwo->getId(), *ovMachineTwo);
    corpTwo->addMachine(ovMachineThree->getId(), *ovMachineThree);

    // create company, create machines, setup machines, add machines.
    Company *corpThree = new Company();
    corpThree->setCompanyName("FoodBox");
    VendingMachine *fbMachineOne = new VendingMachine(1, "909 23rd St", MachineModel::TK421);
    VendingMachine *fbMachineTwo = new VendingMachine(2, "2801 14th Ave", MachineModel::TK421);
    VendingMachine *fbMachineThree = new VendingMachine(3, "867 Rock Ct", MachineModel::VM4000);
    VendingMachine *fbMachineFour = new VendingMachine(4, "777 Lucky Ln", MachineModel::Vendtron20);

    fbMachineOne->addItem("A1", *createMountainDew());
    fbMachineOne->addItem("A2", *createMountainDew());
    fbMachineOne->addItem("A3", *createBottledWater());
    fbMachineOne->addItem("A4", *createBottledWater());

    fbMachineTwo->addItem("A1", *createMountainDew());
    fbMachineTwo->addItem("A2", *createMountainDew());
    fbMachineTwo->addItem("A3", *createBottledWater());

    fbMachineThree->addItem("A1", *createEggSaladSandwich());
    fbMachineThree->addItem("A2", *createEggSaladSandwich());
    fbMachineThree->addItem("A3", *createSlimJim());
    fbMachineThree->addItem("A4", *createSlimJim());

    fbMachineFour->addItem("A1", *createMountainDew());
    fbMachineFour->addItem("A2", *createBottledWater());
    fbMachineFour->addItem("A3", *createEggSaladSandwich());
    fbMachineFour->addItem("A4", *createEggSaladSandwich());

    corpThree->addMachine(fbMachineOne->getId(), *fbMachineOne);
    corpThree->addMachine(fbMachineTwo->getId(), *fbMachineTwo);
    corpThree->addMachine(fbMachineThree->getId(), *fbMachineThree);
    corpThree->addMachine(fbMachineFour->getId(), *fbMachineFour);

    // add complete companies to map.
    this->addCompany(corpOne->getCompanyName(), *corpOne);
    this->addCompany(corpTwo->getCompanyName(), *corpTwo);
    this->addCompany(corpThree->getCompanyName(), *corpThree);
}
DataContext::~DataContext()
{

}

bool DataContext::addCompany(string cn, Company &comp)
{
    bool returnVal = false;
    try
    {
        this->companies.at(cn);
    }
    catch (const std::out_of_range& oor)
    {
        this->companies[cn] = &comp;
        returnVal = true;
    }
    return returnVal;
}

bool DataContext::removeCompany(string cn)
{
    int companiesRemoved = this->companies.erase(cn);

    if (companiesRemoved > 0){
        return true;
    }
    else{
        return false;
    }
}

Company* DataContext::getCompanyByName(string cn)
{
    Company* returnVal;

    try
    {
        returnVal = this->companies.at(cn);
    }
    catch (const std::out_of_range& oor)
    {
        returnVal = nullptr;
    }
    return returnVal;
}

Item* DataContext::createMountainDew(){
    Item *returnValue = new Item();

    returnValue->setName("Mountain Dew");
    returnValue->setQuantity(12);
    returnValue->setSize(20.0);
    returnValue->setSizeUnits("Fluid Ounce");

    return returnValue;
}

Item* DataContext::createBottledWater(){
    Item *returnValue = new Item();

    returnValue->setName("Aquafina");
    returnValue->setQuantity(12);
    returnValue->setSize(20.0);
    returnValue->setSizeUnits("Fluid Ounce");

    return returnValue;
}

Item* DataContext::createSlimJim(){
    Item *returnValue = new Item();

    returnValue->setName("Slim Jim");
    returnValue->setQuantity(25);
    returnValue->setSize(2);
    returnValue->setSizeUnits("Ounce");

    return returnValue;
}

Item* DataContext::createEggSaladSandwich(){
    Item *returnValue = new Item();

    returnValue->setName("Egg Salad Sandwich");
    returnValue->setQuantity(10);
    returnValue->setSize(6);
    returnValue->setSizeUnits("Ounce");

    return returnValue;
}
