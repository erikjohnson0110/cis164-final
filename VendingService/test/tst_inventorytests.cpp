#include <QtTest>

// add necessary includes here

class inventorytests : public QObject
{
    Q_OBJECT

public:
    inventorytests();
    ~inventorytests();

private slots:
    void test_case1();

};

inventorytests::inventorytests()
{

}

inventorytests::~inventorytests()
{

}

void inventorytests::test_case1()
{

}

QTEST_APPLESS_MAIN(inventorytests)

#include "tst_inventorytests.moc"
