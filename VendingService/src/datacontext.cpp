#include <memory>
#include "datacontext.h"
#include "enums.h"

// I am not using a database for this project.  This constructor will
// initialize all program data.
DataContext::DataContext()
{
    // create company, create machines, setup machines, add machines.
    unique_ptr<Company> corpOne = make_unique<Company>();
    corpOne->setCompanyName("Mego-Corp");
    unique_ptr<VendingMachine> mcMachineOne = make_unique<VendingMachine>(1, "123 Main St", MachineModel::TK421);
    unique_ptr<VendingMachine> mcMachineTwo = make_unique<VendingMachine>(2, "2000 64th Ave", MachineModel::VM4000);
    unique_ptr<VendingMachine> mcMachineThree = make_unique<VendingMachine>(3, "475 Fake Blvd", MachineModel::VM4000);

    //unique_ptr<Item> itemOne = make_unique<Item>();
    //itemOne->setName("Mountain Dew");
    //itemOne->setQuantity(12);
    //itemOne->setSize(20.0);
    //itemOne->setSizeUnits("Fluid Ounce");
    //mcMachineOne->addItem("A1", itemOne);

    corpOne->addMachine(mcMachineOne->getId(), *mcMachineOne);
    corpOne->addMachine(mcMachineTwo->getId(), *mcMachineTwo);
    corpOne->addMachine(mcMachineThree->getId(), *mcMachineThree);

    // create company, create machines, setup machines, add machines.
    unique_ptr<Company> corpTwo = make_unique<Company>();
    corpTwo->setCompanyName("OfficeVend");
    unique_ptr<VendingMachine> ovMachineOne = make_unique<VendingMachine>(1, "200 Maple St", MachineModel::TK421);
    unique_ptr<VendingMachine> ovMachineTwo = make_unique<VendingMachine>(2, "303 2nd St", MachineModel::FoodBoxXD);
    unique_ptr<VendingMachine> ovMachineThree = make_unique<VendingMachine>(3, "1020 Quiet Ln", MachineModel::Vendtron20);
    corpTwo->addMachine(ovMachineOne->getId(), *ovMachineOne);
    corpTwo->addMachine(ovMachineTwo->getId(), *ovMachineTwo);
    corpTwo->addMachine(ovMachineThree->getId(), *ovMachineThree);

    // create company, create machines, setup machines, add machines.
    unique_ptr<Company> corpThree = make_unique<Company>();
    corpThree->setCompanyName("FoodBox");
    unique_ptr<VendingMachine> fbMachineOne = make_unique<VendingMachine>(1, "909 23rd St", MachineModel::TK421);
    unique_ptr<VendingMachine> fbMachineTwo = make_unique<VendingMachine>(2, "2801 14th Ave", MachineModel::TK421);
    unique_ptr<VendingMachine> fbMachineThree = make_unique<VendingMachine>(3, "867 Rock Ct", MachineModel::VM4000);
    unique_ptr<VendingMachine> fbMachineFour = make_unique<VendingMachine>(4, "777 Lucky Ln", MachineModel::Vendtron20);
    corpThree->addMachine(fbMachineOne->getId(), *fbMachineOne);
    corpThree->addMachine(fbMachineTwo->getId(), *fbMachineTwo);
    corpThree->addMachine(fbMachineThree->getId(), *fbMachineThree);
    corpThree->addMachine(fbMachineFour->getId(), *fbMachineFour);



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
