#include "HTMLFile.h"
#include <vector>

void HTMLFile::writeToFile(std::vector<Coats> shopping) const {
    std::ofstream file(this->filename);
    file << "<!DOCTYPE html>\n";
    file << "<html>\n";
    file << "<head>\n";
    file << "<title>Shopping</title>\n";
    file << "</head>\n";
    file << "<body>\n";
    file << "<table border=\"1\">\n";
    file << "<tr>\n";
    file << "<td>Size</td>\n";
    file << "<td>Colour</td>\n";
    file << "<td>Price</td>\n";
    file << "<td>Link</td>\n";
    file << "</tr>\n";
    for (auto &coat : shopping) {
        file << "<tr>\n";
        file << "<td>" << coat.getSize() << "</td>\n";
        file << "<td>" << coat.getColour() << "</td>\n";
        file << "<td>" << coat.getPrice() << "</td>\n";
        file << "<td>" << coat.getPhoto() << "</td>\n";
        file << "</tr>\n";
    }
    file << "</table>\n";
    file << "</body>\n";
    file << "</html>\n";
    file.close();
}
