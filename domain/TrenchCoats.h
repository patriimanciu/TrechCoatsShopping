#pragma once
#include <iostream>
#include <string>

class Coats {
private:
    std::string size, colour;
    int price, quantity;
    std::string photo;

public:
    Coats(const std::string &size = "", const std::string &colour = "", int price = 0, int quantity = 0, const std::string &photo = "");
    ~Coats();
    Coats(const Coats &coat);
    Coats &operator=(const Coats &coat);
    bool operator==(const Coats &coat) const;
    std::string getSize() const;
    std::string getColour();
    std::string getPhoto();
    int getPrice();
    int getQuantity() const;
    void setSize(const std::string &size);
    void setColour(const std::string &colour);
    void setPhoto(const std::string &photo);
    void setPrice(int price);
    void setQuantity(int quantity);
    void validatePhoto(const std::string photo);
    void validatePrice(int price);
    void validateQuantity(int quantity);
    void validateCoat();
};

class TrenchException : public std::exception {
private:
    std::string message;
public:
    TrenchException(const char* mesaj) : message(mesaj) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};