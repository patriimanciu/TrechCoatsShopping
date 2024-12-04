#include <QString>
#include "service.h"

class Command {
public:
    virtual ~Command() {}
    virtual void undo() = 0;
    virtual void execute() = 0;
    virtual QString name() const = 0;
};

class AddCommand : public Command {
public:
    AddCommand(Service& service, const Coats& coat)
            : service(service), coat(coat) {}
    void execute() override {
        service.addCoats(coat);
    }
    void undo() override {
        service.deleteCoats(service.getCoatIndex(coat));
    }
    QString name() const override {
        return "Add";
    }

private:
    Service& service;
    Coats coat;
};


class DeleteCommand : public Command {
private:
    Service& service;
    Coats coat;
    int position;

public:
    DeleteCommand(Service& service, int position) : service(service), position(position) {
        coat = service.getCoats().at(position);
    }

    void execute() override {
        service.deleteCoats(this->service.getCoatIndex(coat));
    }

    void undo() override {
        service.addCoats(coat);
    }

    QString name() const override {
        return "Delete";
    }
};

class UpdateCommand : public Command {
private:
    Service& service;
    Coats oldCoat, newCoat;
    int position;

public:
    UpdateCommand(Service& service, int position, const Coats& newCoat) : service(service), position(position), newCoat(newCoat) {
        oldCoat = service.getCoats().at(position);
    }

    void execute() override {
        service.updateCoat(position, newCoat);
    }

    void undo() override {
        service.updateCoat(position, oldCoat);
    }

    QString name() const override {
        return "Update";
    }
};