#include <memory>
#include <iostream>
#include "datacontext.h"
#include "inventory.h"
#include "item.h"
#include "httpserver.h"

int main()
{
    DataContext *dataContext = new DataContext();

    Company *c = dataContext->getCompanyByName("Mego-Corp");
    VendingMachine *v = c->findMachineById(1);
    cout << "Machine Found: Id(" << v->getId() << ") - Address(" << v->getLocation() << ")" << endl << endl;

    HttpServer server;
    server.startServer(*dataContext);

    return 0;
}
