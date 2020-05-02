#include <memory>
#include <iostream>
#include "datacontext.h"
#include "inventory.h"
#include "item.h"
#include "httpserver.h"

int main()
{
    DataContext *dataContext = new DataContext();

    HttpServer server;
    server.startServer(*dataContext);

    return 0;
}
