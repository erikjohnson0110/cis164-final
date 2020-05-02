#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <iostream>
#include <sstream>
#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDir>
#include <sstream>
#include <httplib.h>
#include <datacontext.h>

using namespace std;
using namespace httplib;

class HttpServer {
private:
    char* domain = "localhost";
    int port = 8080;
    string errorPage = "http://" + string(domain) + ":" + std::to_string(port) + "/error";
public:
    void startServer (DataContext dc) {
        Server svr;

        svr.Get("/", [this](const Request&, Response& res) {
            stringstream body;
            body << "<html><h1>Welcome to the VendoMatic(c) API</h1>";
            body << "<p>The API domain is http://localhost:" << this->port << "</p>";

            body << "<h1 style=\"margin-top: 50px;\">API Endpoints</h1>";

            body << "<h3>GET - /machines/{name}</h3>" ;
            body << "<p>Parameters:</p>";
            body << "<p>@name - (company name)</p>";
            body << "<p style=\"margin-bottom: 50px;\">Example: http://domain:port/machines/?name=Mego-Corp</p>";

            body << "<h3>GET - /machineStatus/{name},{machineId}</h3>" ;
            body << "<p>Parameters:</p>";
            body << "<p>@name - (company name)</p>";
            body << "<p>@machineId - (Vending Machine ID)</p>";
            body << "<p style=\"margin-bottom: 50px;\">Example: http://domain:port/machineStatus/?name=Mego-Corp&machineId=1</p>";

            body << "<h3>GET - /activateMachine/{name},{machineId}</h3>" ;
            body << "<p>Parameters:</p>";
            body << "<p>@name - (company name)</p>";
            body << "<p>@machineId - (Vending Machine ID)</p>";
            body << "<p style=\"margin-bottom: 50px;\">Example: http://domain:port/activateMachine/?name=Mego-Corp&machineId=1</p>";

            body << "<h3>GET - /deactivateMachine/{name},{machineId}</h3>" ;
            body << "<p>Parameters:</p>";
            body << "<p>@name - (company name)</p>";
            body << "<p>@machineId - (Vending Machine ID)</p>";
            body << "<p style=\"margin-bottom: 50px;\">Example: http://domain:port/deactivateMachine/?name=Mego-Corp&machineId=1</p>";

            body << "<h3>GET - /sellItem/{name},{machineId},{vendCode}</h3>" ;
            body << "<p>Parameters:</p>";
            body << "<p>@name - (company name)</p>";
            body << "<p>@machineId - (Vending Machine ID)</p>";
            body << "<p style=\"margin-bottom: 50px;\">Example: http://domain:port/sellItem/?name=Mego-Corp&machineId=1&vendCode=A1</p>";

            body << "<p>INSERT API RESOURCES HERE</p>";
            body << "</html>";
            res.set_content(body.str(), "text/html");
        });

        svr.Get("/error", [this](const Request&, Response& res) {
            stringstream body;
            body << "<html><h1>ERROR</h1>";
            body << "<p>The API endpoint you've requested has encounterd an error." << "</p>";
            body << "<p>Please try again, or contact customer service.</p></html>";
            res.set_content(body.str(), "text/html");
        });

        svr.Get(R"(/test/)", [&](const Request& req, Response& res) {
            res.set_header("Content-Type", "application/json");  // SET Header to indicate response body content is JSON

            QJsonObject jsonObject;

            Company *company = dc.getCompanyByName("Mego-Corp");
            if (company == nullptr){
                cout << "COMPANY NULL" << endl;
            }
            else{
                cout << "COMPANY: " << company->getCompanyName() << endl;
            }

            VendingMachine *machine = company->findMachineById(1);
            if (machine == nullptr){
                cout << "MACHINE NULL" << endl;
            }
            else{
                cout << "MACHINE: " << machine->getId() << endl;
            }

            Item *item = machine->getItemByVendCode("A1");
            if (item == nullptr){
                cout << "ITEM NULL" << endl;
            }
            else{
                cout << "ITEM: " << item->getName() << endl;
            }

            Item *errorItem = new Item();
            errorItem->setName("ERROR ITEM");
            errorItem->setSize(20);
            errorItem->setQuantity(12);
            errorItem->setSizeUnits("Ounce");

            item->writeJson(jsonObject);

            QJsonDocument jsonDocument(jsonObject);
            string jsonString = jsonDocument.toJson().toStdString();

            //stringstream body;
            //body << "{ \"parameter\": \"value\"}";               // add JSON content
            //res.set_content(body.str(), "application/json");     // insert string into body, and indicate body content is json
            res.set_content(jsonString, "application/json");
            //database.close();
        });

        svr.Get(R"(/machines/)", [&](const Request& req, Response& res){
            string corpName = "";
            if (req.has_param("name")){
                corpName = req.get_param_value("name");
            }
            if (corpName.compare("") != 0){
                try {
                    QJsonArray responseObject;
                    Company *company = dc.getCompanyByName(corpName);
                    if (company != nullptr){
                        map<int, VendingMachine*> machineMap = company->getAllMachines();
                        for (pair<int, VendingMachine*> i : machineMap){
                            QJsonObject machineJson;
                            i.second->writeJson(machineJson);
                           responseObject.append(machineJson);
                        }
                        QJsonDocument doc(responseObject);
                        string jsonString = doc.toJson().toStdString();
                        res.set_content(jsonString, "application/json");
                    }
                    else
                    {
                        res.set_redirect(errorPage.c_str());
                    }
                }
                catch (exception ex)
                {
                    cout << "ERROR FINDIGN COMPANY: " << corpName << endl;
                    res.set_redirect(errorPage.c_str());
                }
            }
            else
            {
                res.set_redirect(errorPage.c_str());
            }

        });

        svr.Get(R"(/machineStatus/)", [&](const Request& req, Response& res){
            string corpName = "";
            int machineId = -1;
            if (req.has_param("name") && req.has_param("machineId")){
                corpName = req.get_param_value("name");
                machineId = stoi(req.get_param_value("machineId"));
                Company *company = nullptr;
                try {
                    company = dc.getCompanyByName(corpName);
                } catch (exception ex) {
                    res.set_redirect(errorPage.c_str());
                }

                VendingMachine *machine = nullptr;
                if (company != nullptr){
                    try {
                        machine = company->findMachineById(machineId);
                        QJsonObject responseObject;
                        if (machine != nullptr){
                            responseObject["machineState"] = (machine->isActive() ? "active" : "inactive");
                            QJsonDocument doc(responseObject);
                            string jsonString = doc.toJson().toStdString();
                            res.set_content(jsonString, "application/json");
                        }
                        else
                        {
                           res.set_redirect(errorPage.c_str());
                        }
                    }
                    catch (exception ex) {
                        res.set_redirect(errorPage.c_str());
                    }
                }
                else
                {
                    res.set_redirect(errorPage.c_str());
                }
            }
            else
            {
                res.set_redirect(errorPage.c_str());
            }
        });

        svr.Get(R"(/activateMachine/)", [&](const Request& req, Response& res){
            string corpName = "";
            int machineId = -1;
            if (req.has_param("name") && req.has_param("machineId")){
                corpName = req.get_param_value("name");
                machineId = stoi(req.get_param_value("machineId"));
                Company *company = nullptr;
                try {
                    company = dc.getCompanyByName(corpName);
                } catch (exception ex) {
                    res.set_redirect(errorPage.c_str());
                }

                VendingMachine *machine = nullptr;

                QJsonObject responseObject;
                try {
                    if (company != nullptr){
                        machine = company->findMachineById(machineId);
                        if (machine != nullptr){
                            if (!machine->isActive()){
                                machine->activate();
                                responseObject["responseMessage"] = "activated";
                            }
                            else
                            {
                                responseObject["responseMessage"] = "unable to activate - already active.";
                            }
                            QJsonDocument doc(responseObject);
                            string jsonString = doc.toJson().toStdString();
                            res.set_content(jsonString, "application/json");
                        }
                        else
                        {
                            res.set_redirect(errorPage.c_str());
                        }
                    }
                    else
                    {
                        res.set_redirect(errorPage.c_str());
                    }


                } catch (exception ex) {
                    res.set_redirect(errorPage.c_str());
                }
            }
            else{
                res.set_redirect(errorPage.c_str());
            }
        });

        svr.Get(R"(/deactivateMachine/)", [&](const Request& req, Response& res){
            string corpName = "";
            int machineId = -1;
            if (req.has_param("name") && req.has_param("machineId")){
                corpName = req.get_param_value("name");
                machineId = stoi(req.get_param_value("machineId"));
                Company *company = nullptr;
                try {
                    company = dc.getCompanyByName(corpName);
                } catch (exception ex) {
                    res.set_redirect(errorPage.c_str());
                }

                VendingMachine *machine = nullptr;

                QJsonObject responseObject;
                try {
                    if (company != nullptr){
                        machine = company->findMachineById(machineId);
                        if (machine != nullptr){
                            if (machine->isActive()){
                                machine->deactivate();
                                responseObject["responseMessage"] = "deactivated";
                            }
                            else{
                                responseObject["responseMessage"] = "unable to deactivate - already inactive.";
                            }
                            QJsonDocument doc(responseObject);
                            string jsonString = doc.toJson().toStdString();
                            res.set_content(jsonString, "application/json");
                        }
                        else
                        {
                            res.set_redirect(errorPage.c_str());
                        }
                    }
                    else
                    {
                        res.set_redirect(errorPage.c_str());
                    }
                } catch (exception ex) {
                    res.set_redirect(errorPage.c_str());
                }
            }
            else{
                res.set_redirect(errorPage.c_str());
            }
        });


        svr.Get(R"(/sellItem/)", [&](const Request& req, Response& res){
            string corpName = "";
            int machineId = -1;
            string vendCode = "";
            if (req.has_param("name") && req.has_param("machineId") && req.has_param("vendCode")){
                corpName = req.get_param_value("name");
                machineId = stoi(req.get_param_value("machineId"));
                vendCode = req.get_param_value("vendCode");
                Company *company = nullptr;
                try {
                    company = dc.getCompanyByName(corpName);
                } catch (exception ex) {
                    res.set_redirect(errorPage.c_str());
                }

                VendingMachine *machine = nullptr;

                QJsonObject responseObject;
                try {
                    if (company != nullptr){
                        machine = company->findMachineById(machineId);
                        if (machine != nullptr){
                            Item *item = machine->getItemByVendCode(vendCode);
                            if (item != nullptr){
                                bool sold = false;
                                if (machine->isActive()){
                                    sold = item->sellItem();
                                }
                                if (sold){
                                    machine->setTotalSales((machine->getTotalSales() + item->getPrice()));
                                    responseObject["responseMessage"] = "Item Sold Successfully";
                                }
                                else
                                {
                                    if (!machine->isActive()){
                                        responseObject["responseMessage"] = "Machine Not Active";
                                    }
                                    else{
                                        if (item->getQuantity() == 0){
                                            responseObject["responseMessage"] = "Item Sold Out";
                                        }
                                    }
                                }
                                QJsonDocument doc(responseObject);
                                string jsonString = doc.toJson().toStdString();
                                res.set_content(jsonString, "application/json");
                            }
                            else
                            {
                                res.set_redirect(errorPage.c_str());
                            }
                        }
                        else
                        {
                            res.set_redirect(errorPage.c_str());
                        }
                    }
                    else
                    {
                        res.set_redirect(errorPage.c_str());
                    }
                } catch (exception ex) {
                    res.set_redirect(errorPage.c_str());
                }
            }
            else{
                res.set_redirect(errorPage.c_str());
            }
        });

        svr.Get(R"(/restockItem/)", [&](const Request& req, Response& res){
            string corpName = "";
            int machineId = -1;
            string vendCode = "";
            if (req.has_param("name") && req.has_param("machineId") && req.has_param("vendCode")){
                corpName = req.get_param_value("name");
                machineId = stoi(req.get_param_value("machineId"));
                vendCode = req.get_param_value("vendCode");
                Company *company = nullptr;
                try {
                    company = dc.getCompanyByName(corpName);
                } catch (exception ex) {
                    res.set_redirect(errorPage.c_str());
                }

                VendingMachine *machine = nullptr;

                QJsonObject responseObject;
                try {
                    if (company != nullptr){
                        machine = company->findMachineById(machineId);
                        if (machine != nullptr){
                            Item *item = machine->getItemByVendCode(vendCode);
                            if (item != nullptr){
                                int itemInventory = item->getQuantity();
                                int numAdded = item->getMaxQuantity() - itemInventory;
                                item->setQuantity(item->getMaxQuantity());
                                responseObject["responseMessage"] = "Restock Completed";
                                QJsonDocument doc(responseObject);
                                string jsonString = doc.toJson().toStdString();
                                res.set_content(jsonString, "application/json");
                            }
                            else
                            {
                                res.set_redirect(errorPage.c_str());
                            }
                        }
                        else
                        {
                            res.set_redirect(errorPage.c_str());
                        }
                    }
                    else
                    {
                        res.set_redirect(errorPage.c_str());
                    }
                } catch (exception ex) {
                    res.set_redirect(errorPage.c_str());
                }
            }
            else{
                res.set_redirect(errorPage.c_str());
            }
        });

        cout << "Starting server at http://" << domain << ":" << port << endl;
        svr.listen(domain, port);
    }
};

#endif // HTTPSERVER_H
