#include "ui.h"
#include <iostream>
#include <string>

UI::UI() {
    this->service = Service();
}

UI::~UI() {
}

void UI::printMenu() {
    std::cout << "Welcome!\n";
    std::cout << "Please choose the way you want to run this program today! \n";
    std::cout << "  1. Admin\n";
    std::cout << "  2. Costumer\n";
    std::cout << "      > ";
}


void UI::printAdminMenu() {
    std::cout << "\nMENU: \n";
    std::cout << "1. Add coat. \n";
    std::cout << "2. Delete coat. \n";
    std::cout << "3. Update coat. \n";
    std::cout << "4. See all trench coats in store. \n";
    std::cout << "0. Exit \n";
}

void UI::run() {
    this->printMenu();
    int choice;
    std::cin >> choice;
    if (choice == 1) {
        this->service.setAdmin(true);
        std::cout << "Welcome ADMIN! \n";
        while (true) {
            this->printAdminMenu();
            int option = -1;
            std::cout << "Please enter a command: ";
            std::cin >> option;
            if (option == 1)
                this->addCoatsUI();
            else if (option == 2)
                this->deleteCoatsUI();
            else if (option == 3)
                this->updateCoatsUI();
            else if (option == 4)
                this->printCoats();
            else if (option == 0)
                break;
        }
    }
    else if (choice == 2) {
        this->service.setAdmin(false);
        this->User();
    }
    else {
        std::cout << "Sorry, that's not a valid option, please restart the prgoram. \n";
        return;
    }
    std::cout << "Byee!\n";
}

void UI::addCoatsUI() {
    std::string colour, size, photo;
    int price, quantity;
    std::cout << "Please enter the information about the coat you want to add. \n";
    std::cout << "Colour > ";
    std::cin >> colour;
    std::cout << "Size > ";
    std::cin >> size;
    std::cout << "Price > ";
    std::cin >> price;
    std::cout << "Quantity > ";
    std::cin >> quantity;
    std::cout << "Photo > ";
    std::cin >> photo;
    Coats coat = Coats(size, colour, price, quantity, photo);
    try {
        coat.validateCoat();
    }
    catch (const std::exception &Exception) {
        std::cout << "Something went wrong, try again. ";
        std::cerr << "Error: " << Exception.what() << "\n";
        return;
    }
    if (this->service.addCoats(coat))
        std::cout << "Coat added successfully.\n";
    else
        std::cout << "This coat already exists.\n";
}

void UI::printCoats() {
    std::vector<Coats> coats = this->service.getCoats();
    std::cout << "Total # of coats: " << this->service.getCount() << '\n';
    int i = 1;
    for (const auto &coat : coats) {
        std::cout << i << ") Color: " << coats[i - 1].getColour() << " | Size: " << coats[i - 1].getSize() << " | Price: " << coats[i - 1].getPrice() << " | Quant.: " << coats[i - 1].getQuantity() << " | Photo: " << coats[i - 1].getPhoto() << '\n';
        i++;
    }
}

void UI::deleteCoatsUI() {
    int position;
    std::cout << "Please choose the position of the coat you want to remove.\n";
    std::cout << "> ";
    std::cin >> position;
    try {
        this->service.deleteCoats(position - 1);
        std::cout << "Coat deleted successfully!\n";
    }
    catch (const std::exception &Exception) {
        std::cout << "Something went wrong, try again. ";
        std::cerr << "Error: " << Exception.what() << "\n";
        return;
    }
}

void UI::updateCoatsUI() {
    int position;
    std::cout << "Please choose the position of the coat you want to update.\n";
    std::cout << "> ";
    std::cin >> position;
    std::cout << "Now please give the information you want to update with.\n";

    std::string colour, size, photo;
    int price, quantity;
    std::cout << "Colour > ";
    std::cin >> colour;
    std::cout << "Size > ";
    std::cin >> size;
    std::cout << "Price > ";
    std::cin >> price;
    std::cout << "Quantity > ";
    std::cin >> quantity;
    std::cout << "Photo > ";
    std::cin >> photo;

    Coats coat = Coats(size, colour, price, quantity, photo);
    try {
        coat.validateCoat();
        this->service.updateCoat(position - 1, coat);
        std::cout << "Coat updated sucessfully!\n";
    }
    catch (const std::exception &Exception) {
        std::cout << "Something went wrong, try again. ";
        std::cerr << "Error: " << Exception.what() << "\n";
        return;
    }
}

void UI::User() {
    std::cout << "Okay first off - What type of file would you like to use? \n";
    std::cout << "1. HTML\n";
    std::cout << "2. CSV\n";
    int fileType;
    std::cout << " > ";
    std::cin >> fileType;
    if (fileType != 1 && fileType != 2)
        throw TrenchException("Invalid file type.");
    this->service.setFileType(fileType);
    if (this->service.getFileType() == 1)
        std::cout << "You chose HTML. \n";
    else
        std::cout << "You chose CSV. \n";
    std::cout << "Welcome to our online store! Here's the Trench Coats we currently have in stock.\n";
    int option;
    while (true) {
        option = this->userMenu();
        if (option == 1)
            this->shop();
        else if (option == 2)
            this->seeShoppingBag();
        else if (option == 3) {
            std::string filename;
            std::cout << "Please enter the filename you want to save the shopping bag to: ";
            std::cin >> filename;
            this->service.saveShoppingBag(filename);
        }
        else if (option == 0) {
            this->seeShoppingBag();
            std::string filename;
            std::cout << "Please enter the filename you want to save the shopping bag to: ";
            std::cin >> filename;
            this->service.saveShoppingBag(filename);
            std::cout << "Thank you for visiting our shop! \n";
            break;
        }
        else
            std::cout << "Invalid input.\n";
    }
}


void UI::promptCoat(Coats coat) {
    std::cout << "Colour: " << coat.getColour() << " | Size: " << coat.getSize() << " | Price: " << coat.getPrice()
              << " | Quant.: " << coat.getQuantity() << " | Photo: " << coat.getPhoto() << '\n';
    this->service.openPhotoInBrowser(coat);
    std::cout << "Do you want to add it to cart? (yes/no) > ";
    std::string choice;
    std::cin >> choice;
    if (choice == "yes") {
        this->service.addToCart(coat);
        std::cout << "Your current total is " << this->service.getTotal() << "\n";
    }
}

int UI::userMenu() {
    std::cout << "\nMENU: \n";
    std::cout << "1. Shop for coats.\n";
    std::cout << "2. See shopping bag.\n";
    std::cout << "3. Save shopping bag.\n";
    std::cout << "0. Exit.\n";
    int choice;
    std::cout << "> ";
    std::cin >> choice;
    return choice;
}

void UI::shop() {
    std::cout << "What size are you looking for? > ";
    std::string choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(std::cin, choice);
    if (choice.empty())
        choice = "";
    std::vector<Coats> coats = this->service.getCoatsBySize(choice);
    bool stop = false;
    int size = coats.size(), i = 0;
    while (!stop) {
        this->promptCoat(coats[i % size]);
        i++;
        std::cout << "Do you want to continue? (yes/no) > ";
        std::string keep;
        std::cin >> keep;
        if (keep == "no")
            stop = true;
    }
}

void UI::seeShoppingBag() {
    std::cout << "Here's your shopping bag: \n";
    std::vector<Coats> shop = this->service.getShoppingBag();
    int j = 1;
    for (auto &coat : shop) {
        std::cout << j << ") Color: " << shop[j - 1].getColour() << " | Size: " << shop[j - 1].getSize() << " | Price: "
                  << shop[j - 1].getPrice() << " | Photo: " << shop[j - 1].getPhoto() << '\n';
        j++;
    }
    std::cout << "Your total is: " << this->service.getTotal() << "\n";
}
