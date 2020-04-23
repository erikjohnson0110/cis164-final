#include <memory>
#include <iostream>
#include "inventory.h"
#include "item.h"
#include "httpserver.h"

int main()
{
    unique_ptr<Inventory> inv = make_unique<Inventory>();

    unique_ptr<Item> itemOne = make_unique<Item>();
    itemOne->setName("Mountain Dew");
    itemOne->setQuantity(12);
    itemOne->setSize(20.0);
    itemOne->setSizeUnits("Fluid Ounce");

    unique_ptr<Item> itemTwo = make_unique<Item>();
    itemTwo->setName("Slim Jim");
    itemTwo->setQuantity(25);
    itemTwo->setSize(2);
    itemTwo->setSizeUnits("Ounce");

    bool itemOneIsAdded = inv->addItem("A1", *itemOne);
    cout << (itemOneIsAdded ? "Added Successfully" : "Not Added") << endl;
    bool itemTwoIsAdded = inv->addItem("A2", *itemTwo);
    cout << (itemOneIsAdded ? "Added Successfully" : "Not Added") << endl << endl;

    cout << "Item A1: " << inv->getItemByVendCode("A1")->getName() << endl;
    cout << "Item A2: " << inv->getItemByVendCode("A2")->getName() << endl;

    HttpServer server;
    server.startServer(*itemOne);

    return 0;
}
