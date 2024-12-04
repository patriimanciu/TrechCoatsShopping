#include "../repository/repository.h"

Repository::Repository() {
    this->dataFilename = "../in.txt";
    this->readFromFile();
}

Repository::~Repository() {
    this->saveToFile();
}

void Repository::addCoat(const Coats &coat) {
    this->coats.push_back(coat);
}

std::vector<Coats> Repository::getCoats() const{
    return this->coats;
}

int Repository::getCount() const{
    return this->coats.size();
}

int Repository::getPosition(const Coats &coat) const {
    auto it = std::find(this->coats.begin(), this->coats.end(), coat);
    if (it != this->coats.end()) {
        return std::distance(this->coats.begin(), it);
    }
    return -1;
}

void Repository::deleteCoat(int position) {
    Coats coat = this->coats[position];
    this->coats.erase(this->coats.begin() + position);
}

void Repository::updateCoat(int position, Coats newCoat) {
    if (position < 0 || position >= this->coats.size())
        throw TrenchException("Invalid position");
    this->coats[position] = newCoat;
}

std::vector<Coats> Repository::getCoatsBySize(const std::string &size) {
    std::vector<Coats> newCoats;
    std::copy_if(this->coats.begin(), this->coats.end(), std::back_inserter(newCoats),
                 [&](const Coats &coat) {
                     return (size.empty() && coat.getQuantity() != 0) || (coat.getSize() == size && coat.getQuantity() != 0);
                 });
    return newCoats;
}

void Repository::sell(Coats coat) {
    auto it = std::find(this->coats.begin(), this->coats.end(), coat);
    if (it != this->coats.end()) {
        it->setQuantity(it->getQuantity() - 1);
    }
}

std::istream& operator>>(std::istream& is, Coats& coat) {
    std::string colour, size, photo;
    int price, quantity;
    if (std::getline(is, colour, ',') &&
        std::getline(is, size, ',') &&
        is >> price && is.ignore() &&
        is >> quantity && is.ignore() &&
        std::getline(is, photo)) {
        coat = Coats(colour, size, price, quantity, photo);
    }
    return is;
}

void Repository::saveToFile() {
    std::ofstream file(this->dataFilename);
    if (!file.is_open())
        throw TrenchException("The file could not be opened!");
    for (auto &elem : this->getCoats())
        file << elem.getColour() << "," << elem.getSize() << "," << elem.getPrice() << "," << elem.getQuantity() << "," << elem.getPhoto() << '\n';
    file.close();
}

void Repository::readFromFile() {
    std::ifstream file(this->dataFilename);
    if (!file.is_open())
        throw TrenchException("The file could not be opened!");
    this->coats.clear();
    Coats coat;
    while (file >> coat) {
        this->addCoat(coat);
    }
    file.close();
}
