#include <iostream>
#include <fstream>
#pragma once
#include "../domain/TrenchCoats.h"
#include "File.h"

class HTMLFile : public File {
public:
    HTMLFile(const std::string &filename) : File(filename) {}
    void writeToFile(std::vector<Coats> shopping) const;
};