#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <QJsonObject>

using namespace std;

class Item
{
private:
    string name;
    int quantity;
    double size;
    string sizeUnits;
public:
    Item();
    Item(string, int, double, string);
    ~Item();

    int getQuantity();
    void setQuantity(int);

    string getName();
    void setName(string);

    double getSize();
    void setSize(double);

    string getSizeUnits();
    void setSizeUnits(string);

    void readJson(const QJsonObject &json);
    void writeJson(QJsonObject &json) const;

};

#endif // ITEM_H
