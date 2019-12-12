#ifndef TEST_H
#define TEST_H

#include "thing.h"
#include <float.h>
#include <iostream>
#include <QRandomGenerator>
#include <QDateTime>
#include <QStringList>
#include "list.h"
#include "iterator.h"
#include <QtDebug>


namespace Random
{

double realNumber(double from = -DBL_MAX/2, double to = DBL_MAX/2) {
    return from + (to - from) * QRandomGenerator::global()->generateDouble();
}

int integer(int from = INT_MIN, int to = INT_MAX) {
    return QRandomGenerator::global()->bounded(from, to);
}

QDateTime dateTime(QDateTime from, QDateTime to) {
    return from.addSecs(static_cast<qint64>(QRandomGenerator::global()->
                                            generate64()) % from.secsTo(to));
}

const QString& itemFrom(const QStringList &list) {
    return list.at(QRandomGenerator::global()->bounded(list.length()));
}

QString ingredient() {
    static QStringList ingredients = {"Вода", "Яйцо", "Сахар", "Молоко",
                                      "Картофель", "Соль", "Кефир", "Яблоко",
                                      "Мука", "Масло", "Сосиска", "Хлопья"};
    return itemFrom(ingredients);
}

QString material() {
    static QStringList woodTypes = {"Дуб", "Вишня", "Клён", "Орех",
                                    "Палисандр", "Сосна", "Бук",
                                    "Ясень", "Берёза", "Кедр"};
    return itemFrom(woodTypes);
}

QString aminoacidName() {
    static QStringList aminoacids = {"Глицин", "Аланин", "Валин", "Изолейцин",
                                     "Лейцин", "Пролин", "Серин", "Треонин",
                                     "Цистеин", "Метионин",
                                     "Аспарагиновая кислота", "Аспарагин",
                                     "Глутаминовая кислота", "Глутамин",
                                     "Лизин", "Аргинин", "Гистидин",
                                     "Фенилаланин", "Тирозин", "Триптофан"};
    return itemFrom(aminoacids);
}

QChar aminoacidLetter() {
    static QString letters = "GAVILPSTCMDNEQKRHFYW";
    return letters.at(QRandomGenerator::global()->bounded(letters.length()));
}

QString studentFIO() {
    static QStringList names = {"Алексей", "Анатолий", "Вячеслав", "Георгий",
                                "Евгений", "Кирилл", "Матвей", "Мухаммад",
                                "Никита", "Роман", "Сергей"},
            surnames = {"Игнатьев", "Кабисов", "Кожевников", "Лернер",
                        "Лясковский", "Сафронов", "Умбрас", "Шадько",
                        "Штырлин", "Юсупов", "Якубов"},
            patronymic = {"Александрович", "Андреевич", "Даниилович",
                          "Иванович", "Ильич", "Максимович",
                          "Павлович", "Романович", "Сергеевич", "Юрьевич", ""};
    auto randomGenerator = QRandomGenerator::global();
    return surnames.at(randomGenerator->bounded(surnames.size())) + " " +
            names.at(randomGenerator->bounded(names.size())) + " " +
            patronymic.at(randomGenerator->bounded(patronymic.size()));
}
};

inline std::string stdString(const QString &qstring) {
    return qstring.toLocal8Bit().toStdString();
}

inline char stdChar(const QChar &qchar) {
    return qchar.toLatin1();
}
/*
class YourClass {
private:
    int _param1;
    double _param2;
public:
    int param3;
    double  param4;

    YourClass();
    YourClass(int value1, double value2, int value3, double value4);
    YourClass(const YourClass &other);
    int getParameter1() const;
    double getParameter2() const;
    void setParameter1(int newValue1);
    void setParameter2(double newValue2);
};
*/
#define MIN_VOLUME 0.1
#define MIN_PRICE 0

namespace Test
{
void assertValidity(Thing &object)
{
    assert(object.getVolume() >= MIN_VOLUME);

    assert(object.getPrice() >= MIN_PRICE);
}

void assertEquality(Thing &first,Thing &second)
{
    assert(first.getName() == second.getName());
    assert(first.getVolume() == second.getVolume());

    assert(first.getPrice() == second.getPrice());
}

void assertStability(Thing &object)
{
    int value1 = Random::integer(MIN_VOLUME);
    object.setVolume(value1);
    assert(object.getVolume() == value1);
    int error1 = Random::integer(-999, MIN_VOLUME);
    object.setVolume(error1);
    assert(object.getVolume() != error1);
    assert(object.getVolume() == value1);
    QString name = Random::material();
    object.setName(name);
    assert(object.getName() == name);
    double value2 = Random::realNumber(MIN_PRICE);
    object.setPrice(value2);
    assert(object.getPrice() == value2);
    double error2 = Random::realNumber(-100, MIN_PRICE);
    object.setPrice(error2);
    assert(object.getPrice() == value2);
    assert(object.getPrice() != error2);
}

void assertListCopying(){
    List list1;
    Thing a;
    a.setName(QString("a"));
    a.setVolume(1);
    a.setPrice(1);
    list1.add(a);
    List list2(list1);
    assert(list1 == list2);
}

void assertAddingAndDeleting(){
    List list1;
    Thing a;
    a.setName(QString("a"));
    a.setVolume(1);
    a.setPrice(1);
    Thing b;
    b.setName(QString("b"));
    b.setVolume(2);
    b.setPrice(3);
    int x = list1.len();
    list1.add(a);
    list1.add(b);
    int y = list1.len();
    assert(x == (y-2));
    list1.deleteElement(b);
    assert(list1.len() == (y-1));
    list1.deleteElement(b);
    assert(list1.len() == (y-1));
}

void assertClearing(){
    List list1;
    Thing a;
    a.setName(QString("a"));
    a.setVolume(1);
    a.setPrice(1);
    Thing b;
    b.setName(QString("b"));
    b.setVolume(2);
    b.setPrice(3);
    list1.add(a);
    list1.add(b);
    int x = list1.len();
    list1.clearList();
    List list2;
    assert(list1.len() == 0);
    assert(list2 == list1);
    assert(list1.len() != x);
}

void printList(List &list){
    Iterator itr = list.begin();
    int i = 0;
    for (;itr != list.end(); ++itr){
        if((*itr)->how()){
            Thing *temp = dynamic_cast<Thing*>(*itr);
            qDebug() << i << temp->getInfo();
        }
        else {
            CoinPile *temp = dynamic_cast<CoinPile*>(*itr);
            qDebug() << i << temp->getInfo();
        }

        ++i;
    }
}
void assertIterator(){
    List list1;
    Thing a;
    a.setName(QString("a"));
    a.setVolume(1);
    a.setPrice(1);
    Thing b;
    b.setName(QString("b"));
    b.setVolume(2);
    b.setPrice(3);
    list1.add(a);
    list1.add(b);
    printList(list1);
}

void assertFileWork(){
    List list1;
    Thing a(QString("a"), 1, 1);
    Thing b(QString("b"), 2, 3);
    list1.add(a);
    list1.add(b);
    list1.writeToFile(QString("1"));
    List list2;
    list2.readListFromFile(QString("1"));
    assert(list1 == list2);
}

void run() {
    Thing defaultObject;
    assertValidity(defaultObject);
    for (int i = 0; i < 1000; i++)
    {
        Thing randomObject(Random::material(),
                           Random::realNumber(MIN_PRICE - 10),
                           Random::realNumber(-1e9, 1e9));
        assertValidity(randomObject);
        Thing copyObject(randomObject);
        assertValidity(copyObject);
        assertEquality(randomObject, copyObject);
        assertStability(copyObject);
        assertValidity(copyObject);
    }
    assertListCopying();
    assertClearing();
    assertAddingAndDeleting();
    assertIterator();
    assertFileWork();
    std::cout << "\nВсе тесты успешно пройдены!\n";
}

};


#endif // TEST_H
