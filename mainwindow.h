#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidget>
#include <QMainWindow>
#include "list.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void fillListWidget();

    void on_addThingButton_clicked();

    void on_addCoinPileButton_clicked();

    void on_loadFileButton_clicked();

    void on_saveToFIleButton_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_clearListButton_clicked();

private:
    List list;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
