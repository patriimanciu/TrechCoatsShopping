#include "File.h"
#include <vector>

void File::open(std::vector<Coats> shopping) const {
    this->writeToFile(shopping);
    std::string commandToOpenFile = "open " + this->filename;
    system(commandToOpenFile.c_str());
}
