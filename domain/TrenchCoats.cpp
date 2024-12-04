#include "TrenchCoats.h"
#include <regex>

// constructor & destructor
Coats::Coats(const std::string &size, const std::string &colour, int price, int quantity, const std::string &photo)
        : size(size), colour(colour), price(price), quantity(quantity), photo(photo) {}
Coats::~Coats() {};

// copy
Coats::Coats(const Coats &otherCoat) {
    this->colour = otherCoat.colour;
    this->size = otherCoat.size;
    this->price = otherCoat.price;
    this->quantity = otherCoat.quantity;
    this->photo = otherCoat.photo;
}

// compare
bool Coats::operator==(const Coats &otherCoat) const {
    return (this->size == otherCoat.size) &&
           (this->colour == otherCoat.colour) &&
           (this->price == otherCoat.price) &&
           (this->quantity == otherCoat.quantity) &&
           (this->photo == otherCoat.photo);
}

// assign
Coats &Coats::operator=(const Coats &otherCoat) {
    if (this == &otherCoat)
        return *this;

    this->colour = otherCoat.colour;
    this->size = otherCoat.size;
    this->price = otherCoat.price;
    this->quantity = otherCoat.quantity;
    this->photo = otherCoat.photo;

    return *this;
}

// getters
std::string Coats::getSize() const {
    return this->size;
}

std::string Coats:: getColour() {
    return this->colour;
}

std::string Coats::getPhoto() {
    return this->photo;
}

int Coats::getPrice() {
    return this->price;
}

int Coats::getQuantity() const {
    return this->quantity;
}

// setters
void Coats::setSize(const std::string &size) {
    this->size = size;
}

void Coats::setColour(const std::string &colour) {
    this->colour = colour;
}

void Coats::setPhoto(const std::string &photo) {
    this->photo = photo;
}

void Coats::setPrice(int price) {
    Coats::validatePrice(price);
    this->price = price;
}

void Coats::setQuantity(int quantity) {
    Coats::validateQuantity(quantity);
    this->quantity = quantity;
}

// validators
void Coats::validatePhoto(const std::string photo) {
    if (photo.empty())
        throw TrenchException("Photo cannot be empty.");
    const std::regex pattern("https://i.pinimg.com/[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)");
    if (!std::regex_match(photo, pattern))
        throw TrenchException("Invalid photo link");
}

void Coats::validateQuantity(int quantity) {
    if (quantity < 0)
        throw TrenchException("The quantity must be positive.");
}

void Coats::validatePrice(int price) {
    if (price < 0)
        throw TrenchException("The price must be positive.");
}

void Coats::validateCoat() {
    validatePrice(this->price);
    validateQuantity(this->quantity);
    validatePhoto(this->photo);
}