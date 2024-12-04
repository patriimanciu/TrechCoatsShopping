#include "File.h"
#pragma once
#include "../domain/TrenchCoats.h"

class CSVFile : public File {
public:
    CSVFile(const std::string &filename) : File(filename) {}
    void open();
    void writeToFile(std::vector<Coats> shopping) const;
};