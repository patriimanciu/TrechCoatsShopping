#include "CSVFile.h"
#include "../domain/TrenchCoats.h"
#include <vector>

void CSVFile::writeToFile(std::vector<Coats> shopping) const {
    std::ofstream file(this->filename);
    if (!file.is_open()) {
        throw std::runtime_error("File could not be opened");
    }
    file << "Index, Size, Colour, Price, Link\n";
    int index = 0;

    for (auto coat: shopping) {
        file << index << ", " << coat.getSize() << ", " << coat.getColour() << ", " << coat.getPrice() << ", " << coat.getPhoto() << "\n";
        index++;
    }
    file.close();

}

void CSVFile::open() {
    std::string commandToOpenFile = "open \"" + this->filename + "\""; // Enclose filename in double quotes for paths with spaces
    system(commandToOpenFile.c_str());
}
