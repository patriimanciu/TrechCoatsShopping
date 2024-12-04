#pragma once
#include <qwidget.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qlistwidget.h>
#include <QHBoxLayout>
#include <QTableWidget>
#include "../service/service.h"
#include "commandManager.h"

class GUI : public QWidget {
private:
    Service service;
    QVBoxLayout* mainLayout;
    QListWidget* coatsList;
    QListWidget* shoppingList;
    QLineEdit* sizeEdit;
    QLineEdit* colourEdit;
    QLineEdit* priceEdit;
    QLineEdit* quantityEdit;
    QPushButton* addButton;
    QPushButton* deleteButton;
    QPushButton* updateButton;
    QPushButton* shopButton;
    QPushButton* seeShoppingBagButton;

public:
    GUI();
    void initGUI();
    void adminButtonHandler();
    void userButtonHandler();
};

class NewAdminWindow : public QWidget {
    Q_OBJECT
private:
    Service service;
    QTableWidget* tableWidget;
    void refreshTable() {
        std::vector<Coats> coats = this->service.getCoats();
        tableWidget->setRowCount(coats.size());

        int row = 0;
        for (auto coat : coats) {
            tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(coat.getSize())));
            tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(coat.getColour())));
            tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(coat.getPrice())));
            tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(coat.getQuantity())));
            tableWidget->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(coat.getPhoto())));
            row++;
        }
    }

public:
    NewAdminWindow(Service& service , QWidget *parent = nullptr);
    CommandManager commandManager;
    void seeCoatsList();
    void addCoat();
    void deleteCoat();
    void updateCoat();
    void undoHandler();
    void redoHandler();
};

class NewUserWindow : public QWidget {
    Q_OBJECT
private:
    Service service;

public:
    NewUserWindow(Service& service, QWidget *parent = nullptr);
    void shop();
    void seeShoppingBag();
    void saveShoppingBag();
};