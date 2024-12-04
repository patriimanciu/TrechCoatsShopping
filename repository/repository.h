#pragma once
#include "../domain/TrenchCoats.h"
#include <stdexcept> // for std::invalid_argument
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>

class Repository {
private:
    std::vector<Coats> coats;
    std::string dataFilename;

public:
    Repository();
    ~Repository();
    void addCoat(const Coats &coat);
    std::vector<Coats> getCoats() const;
    int getCount() const;
    int getPosition(const Coats &coat) const;
    void deleteCoat(int position);
    void updateCoat(int position, Coats newCoat);
    std::vector<Coats> getCoatsBySize(const std::string &size);
    void sell(Coats coat);
    void saveToFile();
    void readFromFile();
};