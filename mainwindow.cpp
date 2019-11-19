#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "thing.h"
#include "QMessageBox"
#include "list.h"
#include "iterator.h"
#include "coinpile.h"

#include <QJsonDocument>


using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->list = List();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fillListWidget(){
    Iterator itr = Iterator(list.head);
    for (;itr != list.end(); ++itr) {
        if((*itr)->how()){
            Thing *temp = dynamic_cast<Thing*>(*itr);
            QJsonObject thingJson = temp->getInfo();
            ui->listWidget->addItem(QString("Name: ") + thingJson.value("name").toString() + QString("\n")
                                    + QString("Price: ") + QVariant(thingJson.value("price").toDouble()).toString() + QString("\n")
                                    + QString("Volume: ") + QVariant(thingJson.value("volume").toDouble()).toString());
        }
        else {
            CoinPile *temp = dynamic_cast<CoinPile*>(*itr);
            QJsonObject thingJson = temp->getInfo();
            ui->listWidget->addItem(QString("Name: Coin Pile\n")
                                    + QString("Price: ") + QVariant(thingJson.value("price").toDouble()).toString() + QString("\n")
                                    + QString("Volume: ") + QVariant(temp->getVolume()).toString());
        }

    }
}

void MainWindow::on_addThingButton_clicked()
{
    QString name = ui->thingNameEdit->text();
    ui->thingNameEdit->clear();
    double price, value;
    try {
        price = stod(ui->thingPriceEdit->text().toStdString());
        ui->thingPriceEdit->clear();
    } catch (invalid_argument) {
        ui->thingPriceEdit->clear();
        ui->thingVolumeEdit->clear();
        QMessageBox::warning(this, "Error", "Price must contain only numbers and a point symbol");
        return;
    }
    try {
        value = stod(ui->thingVolumeEdit->text().toStdString());
        ui->thingVolumeEdit->clear();
    } catch (invalid_argument) {
        ui->thingPriceEdit->clear();
        ui->thingVolumeEdit->clear();
        QMessageBox::warning(this, "Error", "Value must contain only numbers and a point symbol");
        return;
    }
    Thing *newThing = new Thing(name, price, value);
    this->list.add(newThing);
    ui->listWidget->clear();
    this->fillListWidget();
}



void MainWindow::on_addCoinPileButton_clicked()
{
    double price;
    try {
        price = stod(ui->pilePriceEdit->text().toStdString());
        ui->pilePriceEdit->clear();
    } catch (invalid_argument) {
        ui->pilePriceEdit->clear();
        QMessageBox::warning(this, "Error", "Price must contain only numbers and a point symbol");
        return;

    }
    CoinPile *newCoinPile = new CoinPile(price);
    this->list.add(newCoinPile);
    ui->listWidget->clear();
    this->fillListWidget();

}

void MainWindow::on_loadFileButton_clicked()
{
    ui->listWidget->clear();
    QString fileName = ui->filePathEdit->text();
    ui->filePathEdit->clear();
    if(fileName.isEmpty()){
        QMessageBox::warning(this, "Error", "Specify file path");
        return;
    }
    this->list.readListFromFile(fileName);
    this->fillListWidget();
}
void MainWindow::on_saveToFIleButton_clicked()
{
    QString fileName = ui->fileNameEdit->text();
    ui->fileNameEdit->clear();
    if(fileName.isEmpty()){
        QMessageBox::warning(this, "Error", "Specify file path");
        return;
    }
    this->list.writeToFile(fileName);
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{

    QStringList data = item->text().split("\n");
    Thing thingToDelete = Thing(data[0].mid(6), data[1].mid(7).toDouble(),
            data[2].mid(8).toDouble());
    this->list.deleteElement(&thingToDelete);
    delete item;
}

void MainWindow::on_clearListButton_clicked()
{
    ui->listWidget->clear();
    this->list.clearList();
}
