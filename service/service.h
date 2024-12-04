#pragma once
#include "../repository/repository.h"
#include <iostream>
#include <string.h>
#include "../file/HTMLFile.h"
#include "../file/CSVFile.h"

class Service {
private:
    Repository repository;
    bool admin; // is 1 one the user has admin credentials and 0 otherwise
    void hardCodedCoats();
    std::vector<Coats> shoppingBag;
    std::string shoppingBagFilename;
    int total;
    // 1 for HTML, 2 for CSV
    int fileType;


public:
    Service();
    ~Service();
    bool addCoats(Coats coat);
    std::vector<Coats> getCoats() const;
    int getCount() const;
    void setAdmin(bool admin);
    bool deleteCoats(int position);
    bool updateCoat(int position, Coats newCoat);
    std::vector<Coats> getCoatsBySize(std::string size);
    void openPhotoInBrowser(Coats coat);
    int getTotal() const;
    void addToCart(Coats coat);
    std::vector<Coats> getShoppingBag();
    void setFileType(int fileType);
    int getFileType() const;
    void saveShoppingBag(std::string filename);
    void saveShoppingBagHTML();
    void saveShoppingBagCSV();

    int getCoatIndex(Coats coats);
};