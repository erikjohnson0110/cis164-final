#include <QtTest>
#include <memory>
#include "item.h"
#include "inventory.h"
#include "inventoryitem.h"

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
    testItem->setSize(20.0);
    testItem->setSizeUnits("Fluid Ounce");

    unique_ptr<InventoryItem> testInvItem = make_unique<InventoryItem>();
    testInvItem->setItem(*testItem);
    testInvItem->setQuantity(12);
    testInvItem->setMaxQuantity(12);

    string testItemCode = "T1";

    bool addResult = inv->addInventoryItem(testItemCode, *testInvItem);
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
    testExistingItem->setSize(20.0);
    testExistingItem->setSizeUnits("Fluid Ounce");

    unique_ptr<InventoryItem> testInvItem = make_unique<InventoryItem>();
    testInvItem->setItem(*testExistingItem);
    testInvItem->setQuantity(12);
    testInvItem->setMaxQuantity(12);

    inv->addInventoryItem(testItemCode, *testInvItem);

    // Attempt to add another item to inventory in slot "T1"
    unique_ptr<Item> testNewItem = make_unique<Item>();
    testNewItem->setName("Big Red Cream Soda");
    testNewItem->setSize(20.0);
    testNewItem->setSizeUnits("Fluid Ounce");

    unique_ptr<InventoryItem> testSecondInvItem = make_unique<InventoryItem>();
    testSecondInvItem->setItem(*testNewItem);
    testSecondInvItem->setQuantity(12);
    testSecondInvItem->setMaxQuantity(12);

    bool addResult = inv->addInventoryItem(testItemCode, *testSecondInvItem);

    QCOMPARE(addResult, false);

}

// Test verifies that when an item is added, it is stored in the inventory
// this is confirmed by comparing the pointers.
void inventorytests::test_case_item_added()
{
    unique_ptr<Inventory> inv = make_unique<Inventory>();

    unique_ptr<Item> testItem = make_unique<Item>();
    testItem->setName("Mountain Dew");
    testItem->setSize(20.0);
    testItem->setSizeUnits("Fluid Ounce");

    unique_ptr<InventoryItem> testInvItem = make_unique<InventoryItem>();
    testInvItem->setItem(*testItem);
    testInvItem->setQuantity(12);
    testInvItem->setMaxQuantity(12);

    string testItemCode = "T1";
    inv->addInventoryItem(testItemCode, *testInvItem);

    InventoryItem *result = inv->getInventoryItemByVendCode(testItemCode);

    QCOMPARE(&(*testInvItem), result);
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
    testExistingItem->setSize(20.0);
    testExistingItem->setSizeUnits("Fluid Ounce");

    unique_ptr<InventoryItem> testExistingInvItem = make_unique<InventoryItem>();
    testExistingInvItem->setItem(*testExistingItem);
    testExistingInvItem->setQuantity(12);
    testExistingInvItem->setMaxQuantity(12);

    inv->addInventoryItem(testItemCode, *testExistingInvItem);

    // Attempt to add another item to inventory in slot "T1"
    unique_ptr<Item> testNewItem = make_unique<Item>();
    testNewItem->setName("Big Red Cream Soda");
    testNewItem->setSize(20.0);
    testNewItem->setSizeUnits("Fluid Ounce");

    unique_ptr<InventoryItem> testNewInvItem = make_unique<InventoryItem>();
    testNewInvItem->setItem(*testNewItem);
    testNewInvItem->setQuantity(12);
    testNewInvItem->setMaxQuantity(12);

    inv->addInventoryItem(testItemCode, *testNewInvItem);

    InventoryItem *result = inv->getInventoryItemByVendCode(testItemCode);
    // verify first item is still in inventory, not second
    QCOMPARE(&(*testExistingInvItem), result);

}

// Test verifies that removeItem returns true if an item was found and removed
void inventorytests::test_case_remove_item_true(){
    unique_ptr<Inventory> inv = make_unique<Inventory>();
    string testItemCode = "T1";

    // Add an item to inventory in slot "T1"
    unique_ptr<Item> testExistingItem = make_unique<Item>();
    testExistingItem->setName("Mountain Dew");
    testExistingItem->setSize(20.0);
    testExistingItem->setSizeUnits("Fluid Ounce");

    unique_ptr<InventoryItem> testInvItem = make_unique<InventoryItem>();
    testInvItem->setItem(*testExistingItem);
    testInvItem->setQuantity(12);
    testInvItem->setMaxQuantity(12);

    inv->addInventoryItem(testItemCode, *testInvItem);

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
    testExistingItem->setSize(20.0);
    testExistingItem->setSizeUnits("Fluid Ounce");

    unique_ptr<InventoryItem> testInvItem = make_unique<InventoryItem>();
    testInvItem->setItem(*testExistingItem);
    testInvItem->setQuantity(12);
    testInvItem->setMaxQuantity(12);

    inv->addInventoryItem(testItemCode, *testInvItem);

    // remove the item
    InventoryItem *result = inv->getInventoryItemByVendCode(testItemCode);
    QCOMPARE(result, &(*testInvItem));
}

// test verifies that getItem returns a nullptr when no item found.
void inventorytests::test_case_get_item_returns_nullptr(){
    unique_ptr<Inventory> inv = make_unique<Inventory>();
    string testItemCode = "T1";

    InventoryItem *result = inv->getInventoryItemByVendCode(testItemCode);
    QCOMPARE(result, nullptr);
}

QTEST_APPLESS_MAIN(inventorytests)

#include "tst_inventorytests.moc"
