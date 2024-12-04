#include <QAbstractTableModel>
#include "service.h"
#pragma once

class ShoppingBasketModel : public QAbstractTableModel {
    Q_OBJECT

public:
    explicit ShoppingBasketModel(Service& service, QObject* parent = nullptr)
            : QAbstractTableModel(parent), service(service) {}

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return service.getShoppingBag().size();
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 4; // size, colour, price, photo
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole) {
            auto coats = service.getShoppingBag();
            Coats& coat = coats.at(index.row());
            switch (index.column()) {
                case 0: return QString::fromStdString(coat.getSize());
                case 1: return QString::fromStdString(coat.getColour());
                case 2: return coat.getPrice();
                case 3: return QString::fromStdString(coat.getPhoto());
            }
        }
        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
            switch (section) {
                case 0: return "Size";
                case 1: return "Colour";
                case 2: return "Price";
                case 3: return "Photo";
            }
        }
        return QVariant();
    }

private:
    Service& service;
};