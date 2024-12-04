#include <iostream>
#include <fstream>
#pragma once
#include "../domain/TrenchCoats.h"

class File {
protected:
    std::string filename;
public:
    File(std::string filename) : filename(filename) {}
    virtual void writeToFile(std::vector<Coats> shopping) const = 0;
    void open(std::vector<Coats> shopping) const;
    virtual ~File() = default;
};