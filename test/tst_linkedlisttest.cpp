#include <QtTest>

// add necessary includes here
#include "LinkedList.h"
#include <cmath>
#include <cfloat>

class LinkedListTest : public QObject
{
    Q_OBJECT

public:
    LinkedListTest();
    ~LinkedListTest();
private:
    constexpr static auto testInt = 42;
    constexpr static auto testDouble = 13.37;
    const std::string testStr {"very very long string to fit on stack to bypass Small String Optimization (sso) 1234567890"};
    const std::string testStrSSO {"SSO"};

private slots:
    void NodesTest();
    void LLTest();
};

LinkedListTest::LinkedListTest()
{

}

LinkedListTest::~LinkedListTest()
{

}

void LinkedListTest::NodesTest()
{

    Node strN(testStr, nullptr, nullptr);
    QVERIFY(strN.data.GetStoredType() == Types::String);
    QVERIFY(strN.data.TryGetString().compare(testStr)==0);
    Node strS(testStrSSO, nullptr, nullptr);
    QVERIFY(strN.data.GetStoredType() == Types::String);
    QVERIFY(strS.data.TryGetString().compare(testStrSSO)==0);
    Node intN(testInt, nullptr, nullptr);
    Node dblN(testDouble, nullptr, nullptr);
    QVERIFY(intN.data.GetStoredType() == Types::Integer);
    QVERIFY(intN.data.TryGetInt()==testInt);
    QVERIFY(dblN.data.GetStoredType() == Types::Double);
    QVERIFY(std::fabs( dblN.data.TryGetDouble() - testDouble ) < DBL_EPSILON);
    strN.data.SetValue(testStrSSO);
    QVERIFY(strN.data.TryGetString().compare(testStrSSO)==0); // check change value from regular string to SSO-optimized
    strN.data.SetValue(testInt); // check type change
    QVERIFY(strN.data.GetStoredType() == Types::Integer);
    QVERIFY(strN.data.TryGetInt()==testInt);

}
void LinkedListTest::LLTest()
{
    LinkedList list(testInt);
    QVERIFY(list.Count()==1);
    list.PushBack(testDouble);
    QVERIFY(list.Count()==2);
    list.PushBack(testStr);
    QVERIFY(list.Count()==3);
    list.GoTail(); // set iterator to last item
    QVERIFY(list.Search(testInt)); // should set iterator to first item
    list.Erase(); // remove head
    QVERIFY(list.Count()==2);
    list.PushFront(testDouble);
    list.PushBack(testDouble);
    list.FindAndEraseAll(testDouble); //  should remove 3 items
    QVERIFY(list.Count()==1);
    list.GoTail();
    QVERIFY(list.GetType() == Types::String);  // last one item
    list.DropList();  // check double-free in destructor (should be no exception)

}

QTEST_APPLESS_MAIN(LinkedListTest)

#include "tst_linkedlisttest.moc"
