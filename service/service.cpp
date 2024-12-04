#include "service.h"

Service::Service() {
    this->repository = Repository();
    this->shoppingBagFilename = "../shoppingBag.txt";
    this->admin = false;
    if (this->repository.getCount() == 0) {
        this->hardCodedCoats();
    }
    this->shoppingBag = std::vector<Coats>();
    this->total = 0;
}

Service::~Service() {
}

bool Service::addCoats(Coats coat) {
    if (this->repository.getPosition(coat) != -1)
        return false;
    this->repository.addCoat(coat);
    return true;
}

std::vector<Coats> Service::getCoats() const {
    return this->repository.getCoats();
}

int Service::getCount() const {
    return this->repository.getCount();
}

void Service::setAdmin(bool admin) {
    this->admin = admin;
}

bool Service::deleteCoats(int position) {
    this->repository.deleteCoat(position);
    return true;
}

bool Service::updateCoat(int position, Coats newCoat) {
    this->repository.updateCoat(position, newCoat);
    return true;
}

void Service::hardCodedCoats() {
    Coats coat1 = Coats("S", "Classic Beige", 120, 2, "https://i.pinimg.com/474x/ef/37/d4/ef37d4fe598b0742bb5cb42413c10470.jpg");
    Coats coat2 = Coats("M", "Military Green", 150, 0, "https://i.pinimg.com/736x/d5/d2/3e/d5d23e2718a757b8784448fe58cdc4a1.jpg");
    Coats coat3 = Coats("XS", "Baby Blue", 125, 3, "https://i.pinimg.com/474x/e5/76/f4/e576f4e53d71a445b103f1a172e26a71.jpg");
    Coats coat4 = Coats("M", "Dark Brown", 130, 2, "https://i.pinimg.com/474x/74/2f/c1/742fc1e6fe6839263bf6809ea59c9d3f.jpg");
    Coats coat5 = Coats("M", "Pare Green", 100, 8, "https://i.pinimg.com/474x/0d/0d/a5/0d0da567a6c730afe926cb70d8b6c94f.jpg");
    Coats coat6 = Coats("L", "Forest Green", 150, 1, "https://i.pinimg.com/474x/fe/a7/d5/fea7d53f013f25ab51e1a98f64cf661d.jpg");
    Coats coat7 = Coats("XS", "Two Tone", 135, 4, "https://i.pinimg.com/474x/33/db/25/33db259e2b81912d310f8e662a8df978.jpg");
    Coats coat8 = Coats("L", "Brown Leather", 170, 3, "https://i.pinimg.com/474x/a1/5c/7c/a15c7c8e10f6680dbef48cae52b54f14.jpg");
    Coats coat9 = Coats("S", "Classic Gray", 125, 5, "https://i.pinimg.com/474x/0f/67/5a/0f675a4ee40c45310f90e5e4d67250c7.jpg");
    Coats coat10 = Coats("M", "Classic Black", 125, 6, "https://i.pinimg.com/736x/f8/7d/c6/f87dc64d7ffecfda5135c105bacc6f7d.jpg");
    this->addCoats(coat1);
    this->addCoats(coat2);
    this->addCoats(coat3);
    this->addCoats(coat4);
    this->addCoats(coat5);
    this->addCoats(coat6);
    this->addCoats(coat7);
    this->addCoats(coat8);
    this->addCoats(coat9);
    this->addCoats(coat10);
}

std::vector<Coats> Service::getCoatsBySize(std::string size) {
    return this->repository.getCoatsBySize(size);
}

void Service::openPhotoInBrowser(Coats coat) {
    std::string command = "open "+ coat.getPhoto();
    system(command.c_str());
}

int Service::getTotal() const {
    return this->total;
}

void Service::addToCart(Coats coat) {
    this->shoppingBag.push_back(coat);
    this->total = this->total + coat.getPrice();
    this->repository.sell(coat);
}

std::vector<Coats> Service::getShoppingBag() {
    return this->shoppingBag;
}

void Service::setFileType(int fileType) {
    this->fileType = fileType;
}

int Service::getFileType() const {
    return this->fileType;
}

void Service::saveShoppingBag(std::string filename) {
    this->shoppingBagFilename = filename;
    if (this->getFileType() == 1)
        this->saveShoppingBagHTML();
    else
        this->saveShoppingBagCSV();
}

void Service::saveShoppingBagHTML() {
    HTMLFile file = HTMLFile(this->shoppingBagFilename);
    file.writeToFile(this->shoppingBag);
    file.open(this->shoppingBag);
}

void Service::saveShoppingBagCSV() {
    CSVFile file = CSVFile(this->shoppingBagFilename);
    file.writeToFile(this->shoppingBag);
    file.open();
}

int Service::getCoatIndex(Coats coats) {
    std::vector<Coats> c = this->getCoats();
    for (int i = 0; i < this->getCount(); i++)
        if (c[i] == coats)
            return i;
    return -1;
}

