#include <QtTest>
#include <memory>
#include "item.h"
#include "inventory.h"

// add necessary includes here

class inventorytests : public QObject
{
    Q_OBJECT

public:
    inventorytests();
    ~inventorytests();

private slots:
    void test_case_add_item_return_true();
    void test_case_add_item_return_false_if_one_exists_already();
    void test_case_item_added();
    void test_case_item_not_added();
    void test_case_remove_item_true();
    void test_case_remove_item_false();
    void test_case_get_item_returns_item();
    void test_case_get_item_returns_nullptr();

};

inventorytests::inventorytests()
{

}

inventorytests::~inventorytests()
{

}

// Test verifies that addItem() returns true if an item is added.
void inventorytests::test_case_add_item_return_true()
{
    unique_ptr<Inventory> inv = make_unique<Inventory>();

    unique_ptr<Item> testItem = make_unique<Item>();
    testItem->setName("Mountain Dew");
    testItem->setQuantity(12);
    testItem->setSize(20.0);
    testItem->setSizeUnits("Fluid Ounce");

    string testItemCode = "T1";

    bool addResult = inv->addItem(testItemCode, *testItem);
    QCOMPARE(addResult, true);

}

// This test verifies that the addItem() function returns false if an item
// already exists in that location.
void inventorytests::test_case_add_item_return_false_if_one_exists_already()
{
    unique_ptr<Inventory> inv = make_unique<Inventory>();
    string testItemCode = "T1";

    // Add an item to inventory in slot "T1"
    unique_ptr<Item> testExistingItem = make_unique<Item>();
    testExistingItem->setName("Mountain Dew");
    testExistingItem->setQuantity(12);
    testExistingItem->setSize(20.0);
    testExistingItem->setSizeUnits("Fluid Ounce");
    inv->addItem(testItemCode, *testExistingItem);

    // Attempt to add another item to inventory in slot "T1"
    unique_ptr<Item> testNewItem = make_unique<Item>();
    testNewItem->setName("Big Red Cream Soda");
    testNewItem->setQuantity(12);
    testNewItem->setSize(20.0);
    testNewItem->setSizeUnits("Fluid Ounce");
    bool addResult = inv->addItem(testItemCode, *testNewItem);

    QCOMPARE(addResult, false);

}

// Test verifies that when an item is added, it is stored in the inventory
// this is confirmed by comparing the pointers.
void inventorytests::test_case_item_added()
{
    unique_ptr<Inventory> inv = make_unique<Inventory>();

    unique_ptr<Item> testItem = make_unique<Item>();
    testItem->setName("Mountain Dew");
    testItem->setQuantity(12);
    testItem->setSize(20.0);
    testItem->setSizeUnits("Fluid Ounce");

    string testItemCode = "T1";
    inv->addItem(testItemCode, *testItem);

    Item *result = inv->getItemByVendCode(testItemCode);

    QCOMPARE(&(*testItem), result);
}

// test confirms that when an item is not successfully added
// that the map points to the original item, not the one unsuccessfully added
void inventorytests::test_case_item_not_added()
{
    unique_ptr<Inventory> inv = make_unique<Inventory>();
    string testItemCode = "T1";

    // Add an item to inventory in slot "T1"
    unique_ptr<Item> testExistingItem = make_unique<Item>();
    testExistingItem->setName("Mountain Dew");
    testExistingItem->setQuantity(12);
    testExistingItem->setSize(20.0);
    testExistingItem->setSizeUnits("Fluid Ounce");
    inv->addItem(testItemCode, *testExistingItem);

    // Attempt to add another item to inventory in slot "T1"
    unique_ptr<Item> testNewItem = make_unique<Item>();
    testNewItem->setName("Big Red Cream Soda");
    testNewItem->setQuantity(12);
    testNewItem->setSize(20.0);
    testNewItem->setSizeUnits("Fluid Ounce");
    inv->addItem(testItemCode, *testNewItem);

    Item *result = inv->getItemByVendCode(testItemCode);
    // verify first item is still in inventory, not second
    QCOMPARE(&(*testExistingItem), result);

}

// Test verifies that removeItem returns true if an item was found and removed
void inventorytests::test_case_remove_item_true(){
    unique_ptr<Inventory> inv = make_unique<Inventory>();
    string testItemCode = "T1";

    // Add an item to inventory in slot "T1"
    unique_ptr<Item> testExistingItem = make_unique<Item>();
    testExistingItem->setName("Mountain Dew");
    testExistingItem->setQuantity(12);
    testExistingItem->setSize(20.0);
    testExistingItem->setSizeUnits("Fluid Ounce");
    inv->addItem(testItemCode, *testExistingItem);

    // remove the item
    bool result = inv->removeItem(testItemCode);
    QCOMPARE(result, true);

}

// Test verifies that removeItem returns false if an item was not found and removed.
void inventorytests::test_case_remove_item_false(){
    unique_ptr<Inventory> inv = make_unique<Inventory>();
    string testItemCode = "T1";

    bool result = inv->removeItem(testItemCode);
    QCOMPARE(result, false);
}

// test verifies that getItem returns a pointer to the original item
void inventorytests::test_case_get_item_returns_item(){
    unique_ptr<Inventory> inv = make_unique<Inventory>();
    string testItemCode = "T1";

    // Add an item to inventory in slot "T1"
    unique_ptr<Item> testExistingItem = make_unique<Item>();
    testExistingItem->setName("Mountain Dew");
    testExistingItem->setQuantity(12);
    testExistingItem->setSize(20.0);
    testExistingItem->setSizeUnits("Fluid Ounce");
    inv->addItem(testItemCode, *testExistingItem);

    // remove the item
    Item *result = inv->getItemByVendCode(testItemCode);
    QCOMPARE(result, &(*testExistingItem));
}

// test verifies that getItem returns a nullptr when no item found.
void inventorytests::test_case_get_item_returns_nullptr(){
    unique_ptr<Inventory> inv = make_unique<Inventory>();
    string testItemCode = "T1";

    Item *result = inv->getItemByVendCode(testItemCode);
    QCOMPARE(result, nullptr);
}

QTEST_APPLESS_MAIN(inventorytests)

#include "tst_inventorytests.moc"
