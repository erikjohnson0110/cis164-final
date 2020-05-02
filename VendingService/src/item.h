#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <QJsonObject>

using namespace std;

class Item
{
private:
    string name;
    double price;
    double size;
    string sizeUnits;
public:
    Item();
    Item(string, double, double, string);
    ~Item();

    string getName();
    void setName(string);

    double getPrice();
    void setPrice(double);

    double getSize();
    void setSize(double);

    string getSizeUnits();
    void setSizeUnits(string);

    void readJson(const QJsonObject &json);
    void writeJson(QJsonObject &json) const;

};

#endif // ITEM_H
