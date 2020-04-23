#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <iostream>
#include <sstream>
#include <QCoreApplication>
#include <QDir>
#include <sstream>
#include <httplib.h>
#include <item.h>
#include <QJsonDocument>

using namespace std;
using namespace httplib;

class HttpServer {
private:
    char* domain = "localhost";
    int port = 8080;
public:
    void startServer (Item item) {
        Server svr;

        svr.Get("/", [this](const Request&, Response& res) {
            stringstream body;
            body << "<html><h1>Welcome to the VendoMatic(c) API</h1>";
            body << "<p>The API endpoint is http://localhost:" << this->port << "</p>";
            body << "<p>INSERT API RESOURCES HERE</p></html>";
            res.set_content(body.str(), "text/html");
        });

        svr.Get(R"(/test/)", [&](const Request& req, Response& res) {
            res.set_header("Content-Type", "application/json");  // SET Header to indicate response body content is JSON

            QJsonObject jsonObject;
            item.writeJson(jsonObject);

            QJsonDocument jsonDocument(jsonObject);
            string jsonString = jsonDocument.toJson().toStdString();

            //stringstream body;
            //body << "{ \"parameter\": \"value\"}";               // add JSON content
            //res.set_content(body.str(), "application/json");     // insert string into body, and indicate body content is json
            res.set_content(jsonString, "application/json");
            //database.close();
        });

        cout << "Starting server at http://" << domain << ":" << port << endl;
        svr.listen(domain, port);
    }
};

#endif // HTTPSERVER_H
