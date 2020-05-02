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

    mcMachineOne->addInventoryItem("A1", *createMountainDew(20,20));
    mcMachineOne->addInventoryItem("A2", *createMountainDew(20,20));
    mcMachineOne->addInventoryItem("A3", *createBottledWater(20,20));
    mcMachineOne->addInventoryItem("A4", *createBottledWater(20,20));

    mcMachineTwo->addInventoryItem("A1", *createSlimJim(50,50));
    mcMachineTwo->addInventoryItem("A2", *createEggSaladSandwich(10,10));

    mcMachineThree->addInventoryItem("A1", *createSlimJim(50,50));
    mcMachineThree->addInventoryItem("A2", *createEggSaladSandwich(10,10));
    mcMachineThree->addInventoryItem("A3", *createEggSaladSandwich(10,10));
    mcMachineThree->addInventoryItem("A4", *createEggSaladSandwich(10,10));


    corpOne->addMachine(mcMachineOne->getId(), *mcMachineOne);
    corpOne->addMachine(mcMachineTwo->getId(), *mcMachineTwo);
    corpOne->addMachine(mcMachineThree->getId(), *mcMachineThree);

    // create company, create machines, setup machines, add machines.
    Company *corpTwo = new Company();
    corpTwo->setCompanyName("OfficeVend");
    VendingMachine *ovMachineOne = new VendingMachine(1, "200 Maple St", MachineModel::TK421);
    VendingMachine *ovMachineTwo = new VendingMachine(2, "303 2nd St", MachineModel::FoodBoxXD);
    VendingMachine *ovMachineThree = new VendingMachine(3, "1020 Quiet Ln", MachineModel::Vendtron20);

    ovMachineOne->addInventoryItem("A1", *createMountainDew(20,20));
    ovMachineOne->addInventoryItem("A2", *createMountainDew(20,20));
    ovMachineOne->addInventoryItem("A3", *createBottledWater(20,20));

    ovMachineTwo->addInventoryItem("A1", *createSlimJim(50,50));
    ovMachineTwo->addInventoryItem("A2", *createEggSaladSandwich(10,10));
    ovMachineTwo->addInventoryItem("A3", *createEggSaladSandwich(10,10));
    ovMachineTwo->addInventoryItem("A4", *createEggSaladSandwich(10,10));

    ovMachineThree->addInventoryItem("A1", *createSlimJim(50,50));
    ovMachineThree->addInventoryItem("A2", *createEggSaladSandwich(10,10));
    ovMachineThree->addInventoryItem("A3", *createMountainDew(20,20));
    ovMachineThree->addInventoryItem("A4", *createBottledWater(20,20));

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

    fbMachineOne->addInventoryItem("A1", *createMountainDew(20,20));
    fbMachineOne->addInventoryItem("A2", *createMountainDew(20,20));
    fbMachineOne->addInventoryItem("A3", *createBottledWater(20,20));
    fbMachineOne->addInventoryItem("A4", *createBottledWater(20,20));

    fbMachineTwo->addInventoryItem("A1", *createMountainDew(20,20));
    fbMachineTwo->addInventoryItem("A2", *createMountainDew(20,20));
    fbMachineTwo->addInventoryItem("A3", *createBottledWater(20,20));

    fbMachineThree->addInventoryItem("A1", *createEggSaladSandwich(10,10));
    fbMachineThree->addInventoryItem("A2", *createEggSaladSandwich(10,10));
    fbMachineThree->addInventoryItem("A3", *createSlimJim(50,50));
    fbMachineThree->addInventoryItem("A4", *createSlimJim(50,50));

    fbMachineFour->addInventoryItem("A1", *createMountainDew(20,20));
    fbMachineFour->addInventoryItem("A2", *createBottledWater(20,20));
    fbMachineFour->addInventoryItem("A3", *createEggSaladSandwich(10,10));
    fbMachineFour->addInventoryItem("A4", *createEggSaladSandwich(10,10));

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

InventoryItem* DataContext::createMountainDew(int q, int mq){
    InventoryItem *returnValue = new InventoryItem();
    Item *md = new Item();
    md->setName("Mountain Dew");
    md->setPrice(1.49);
    md->setSize(20.0);
    md->setSizeUnits("Fluid Ounce");

    returnValue->setItem(*md);
    returnValue->setQuantity(q);
    returnValue->setMaxQuantity(mq);

    return returnValue;
}

InventoryItem* DataContext::createBottledWater(int q, int mq){
    InventoryItem *returnValue = new InventoryItem();
    Item *bw = new Item();

    bw->setName("Aquafina");
    bw->setPrice(1.49);
    bw->setSize(20.0);
    bw->setSizeUnits("Fluid Ounce");

    returnValue->setItem(*bw);
    returnValue->setQuantity(q);
    returnValue->setMaxQuantity(mq);

    return returnValue;
}

InventoryItem* DataContext::createSlimJim(int q, int mq){
    InventoryItem *returnValue = new InventoryItem();
    Item *sj = new Item();

    sj->setName("Slim Jim");
    sj->setPrice(0.99);
    sj->setSize(2);
    sj->setSizeUnits("Ounce");

    returnValue->setItem(*sj);
    returnValue->setQuantity(q);
    returnValue->setMaxQuantity(mq);

    return returnValue;
}

InventoryItem* DataContext::createEggSaladSandwich(int q, int mq){
    InventoryItem *returnValue = new InventoryItem();
    Item *es = new Item();

    es->setName("Egg Salad Sandwich");
    es->setPrice(2.49);
    es->setSize(6);
    es->setSizeUnits("Ounce");

    returnValue->setItem(*es);
    returnValue->setQuantity(q);
    returnValue->setMaxQuantity(mq);

    return returnValue;
}
