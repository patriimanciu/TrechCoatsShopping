#pragma once
#include "../service/service.h"
#include <iostream>
#include <string.h>

class UI {
private:
    Service service;

public:
    UI();
    ~UI();
    void printMenu();
    void User();
    int userMenu();
    void printAdminMenu();
    void run();
    void addCoatsUI();
    void printCoats();
    void deleteCoatsUI();
    void updateCoatsUI();
    void promptCoat(Coats coat);
    void shop();
    void seeShoppingBag();

};