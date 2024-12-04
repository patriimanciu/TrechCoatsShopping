#include <QDialog>
#include <QTableView>
#include <QVBoxLayout>
#include "shoppingBasket.h"
#pragma once

class ShoppingBasketDialog : public QDialog {
    Q_OBJECT

public:
    explicit ShoppingBasketDialog(Service& service, QWidget* parent = nullptr)
            : QDialog(parent), model(service, this) {
        QVBoxLayout* layout = new QVBoxLayout(this);
        QTableView* tableView = new QTableView(this);
        tableView->setModel(&model);
        layout->addWidget(tableView);
        setLayout(layout);
        setWindowTitle("Shopping Basket");
    }

private:
    ShoppingBasketModel model;
};
