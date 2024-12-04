#include "gui.h"
#include <qlayout.h>
#include <qlabel.h>
#include <QMessageBox>
#include <QTableWidget>
#include <QHeaderView>
#include <QInputDialog>
#include <QShortcut>
#include "dialog.h"
#include "shoppingBasket.h"


GUI::GUI() {
    this->service = Service();
    this->initGUI();
}

void GUI::initGUI() {
    mainLayout = new QVBoxLayout{ this };

    QVBoxLayout* labelLayout = new QVBoxLayout;
    QLabel* welcome = new QLabel{"Welcome! \n"};
    labelLayout->addWidget(welcome);
    QLabel* firstMenu = new QLabel{"Please choose the way you want to run this program today! \n"};
    labelLayout->addWidget(firstMenu);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    QPushButton* adminButton = new QPushButton{"Admin"};
    buttonLayout->addWidget(adminButton);
    connect(adminButton, &QPushButton::clicked, this, &GUI::adminButtonHandler);
    QPushButton* userButton = new QPushButton{"User"};
    buttonLayout->addWidget(userButton);
    connect(userButton, &QPushButton::clicked, this, &GUI::userButtonHandler);

    mainLayout->addLayout(labelLayout);
    mainLayout->addLayout(buttonLayout);
}


void GUI::adminButtonHandler() {
    qDebug() << "Admin button clicked!";
    NewAdminWindow* adminWindow = new NewAdminWindow(this->service);
    adminWindow->show();
    this->close();
}

void GUI::userButtonHandler() {
    qDebug() << "User button clicked!";
    NewUserWindow* userWindow = new NewUserWindow(this->service);
    userWindow->show();
    this->close();
}


void NewAdminWindow::undoHandler() {
    qDebug() << "Undo action triggered!";
    if (commandManager.undoIsEmpty()) {
        QMessageBox::critical(this, "Error", "No more undos available!");
        return;
    }
    commandManager.undo();
    refreshTable();
}

void NewAdminWindow::redoHandler() {
    qDebug() << "Redo action triggered!";
    if (commandManager.redoIsEmpty()) {
        QMessageBox::critical(this, "Error", "No more redos available!");
        return;
    }
    commandManager.redo();
    refreshTable();
}


NewAdminWindow::NewAdminWindow(Service& service, QWidget *parent) {
    this->service = service;

    QShortcut* undoShortcut = new QShortcut(QKeySequence("Ctrl+Z"), this);
    connect(undoShortcut, &QShortcut::activated, this, &NewAdminWindow::undoHandler);
    QShortcut* redoShortcut = new QShortcut(QKeySequence("Ctrl+Y"), this);
    connect(redoShortcut, &QShortcut::activated, this, &NewAdminWindow::redoHandler);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    // QLabel *menuLabel = new QLabel("MENU:", this);
    // layout->addWidget(menuLabel);

    tableWidget = new QTableWidget();
    tableWidget->setColumnCount(5);
    tableWidget->setHorizontalHeaderLabels(QStringList() << "Size" << "Colour" << "Price" << "Quantity" << "Photo");
    tableWidget->verticalHeader()->setVisible(false);
    refreshTable();

    tableWidget->resizeColumnsToContents();
    tableWidget->resize(tableWidget->horizontalHeader()->length(), tableWidget->verticalHeader()->length());

    mainLayout->addWidget(tableWidget);

    QPushButton *addCoatButton = new QPushButton("Add coat.", this);
    layout->addWidget(addCoatButton);
    connect(addCoatButton, &QPushButton::clicked, this, &NewAdminWindow::addCoat);
    QPushButton *deleteCoatButton = new QPushButton("Delete coat.", this);
    layout->addWidget(deleteCoatButton);
    connect(deleteCoatButton, &QPushButton::clicked, this, &NewAdminWindow::deleteCoat);
    QPushButton *updateCoatButton = new QPushButton("Update coat.", this);
    layout->addWidget(updateCoatButton);
    connect(updateCoatButton, &QPushButton::clicked, this, &NewAdminWindow::updateCoat);
    QPushButton *seeCoatsButton = new QPushButton("See all trench coats in store.", this);
    layout->addWidget(seeCoatsButton);
    connect(seeCoatsButton, &QPushButton::clicked, this, &NewAdminWindow::seeCoatsList);
    QPushButton *exitButton = new QPushButton("Exit", this);
    layout->addWidget(exitButton);
    connect(exitButton, &QPushButton::clicked, this, &QWidget::close);


    QPushButton* undoButton = new QPushButton{"Undo"};
    layout->addWidget(undoButton);
    connect(undoButton, &QPushButton::clicked, this, &NewAdminWindow::undoHandler);
    QPushButton* redoButton = new QPushButton{"Redo"};
    layout->addWidget(redoButton);
    connect(redoButton, &QPushButton::clicked, this, &NewAdminWindow::redoHandler);

    mainLayout->addLayout(layout);

    setWindowTitle("Admin Window");
    resize(400, 300);
}

void NewAdminWindow::seeCoatsList()
{
    std::vector<Coats> coats = this->service.getCoats();

    QTableWidget* tableWidget = new QTableWidget(coats.size(), 5);
    tableWidget->setHorizontalHeaderLabels(QStringList() << "Size" << "Colour"  << "Price" << "Quantity" << "Photo");
    tableWidget->verticalHeader()->setVisible(false);

    int row = 0;
    for (auto coat : coats) {
        tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(coat.getColour())));
        tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(coat.getSize())));
        tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(coat.getPrice())));
        tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(coat.getQuantity())));
        tableWidget->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(coat.getPhoto())));
        row++;
    }

    tableWidget->resizeColumnsToContents();
    tableWidget->resize(tableWidget->horizontalHeader()->length(), tableWidget->verticalHeader()->length());

    tableWidget->show();
}

void NewAdminWindow::addCoat()
{
    QLabel* colourLabel = new QLabel("Colour:");
    QLineEdit* colourLineEdit = new QLineEdit;
    QLabel* sizeLabel = new QLabel("Size:");
    QLineEdit* sizeLineEdit = new QLineEdit;
    QLabel* priceLabel = new QLabel("Price:");
    QLineEdit* priceLineEdit = new QLineEdit;
    QLabel* quantityLabel = new QLabel("Quantity:");
    QLineEdit* quantityLineEdit = new QLineEdit;
    QLabel* photoLabel = new QLabel("Photo:");
    QLineEdit* photoLineEdit = new QLineEdit;

    QPushButton* addButton = new QPushButton("Add Coat");

    connect(addButton, &QPushButton::clicked, [=]() {
        std::string colour = colourLineEdit->text().toStdString();
        std::string size = sizeLineEdit->text().toStdString();
        int price = priceLineEdit->text().toInt();
        int quantity = quantityLineEdit->text().toInt();
        std::string photo = photoLineEdit->text().toStdString();

        Coats coat = Coats(size, colour, price, quantity, photo);

        try {
            coat.validateCoat();
        }
        catch (const std::exception& Exception) {
            QMessageBox::critical(this, "Error", QString::fromStdString(Exception.what()));
            return;
        }
        this->commandManager.executeCommand(new AddCommand(this->service, coat));
        colourLineEdit->clear();
        sizeLineEdit->clear();
        priceLineEdit->clear();
        quantityLineEdit->clear();
        photoLineEdit->clear();
    });

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(colourLabel);
    layout->addWidget(colourLineEdit);
    layout->addWidget(sizeLabel);
    layout->addWidget(sizeLineEdit);
    layout->addWidget(priceLabel);
    layout->addWidget(priceLineEdit);
    layout->addWidget(quantityLabel);
    layout->addWidget(quantityLineEdit);
    layout->addWidget(photoLabel);
    layout->addWidget(photoLineEdit);
    layout->addWidget(addButton);

    QDialog* dialog = new QDialog;
    dialog->setLayout(layout);
    dialog->setWindowTitle("Add Coat");
    dialog->exec();
    refreshTable();
}

void NewAdminWindow::deleteCoat()
{
    QLabel* positionLabel = new QLabel("Position:");
    QLineEdit* positionLineEdit = new QLineEdit;
    QPushButton* deleteButton = new QPushButton("Delete Coat");

    connect(deleteButton, &QPushButton::clicked, [=]() {
        int position = positionLineEdit->text().toInt();

        try {
            this->commandManager.executeCommand(new DeleteCommand(this->service, position));
            QMessageBox::information(this, "Success", "Coat deleted successfully!");
        }
        catch (const std::exception& Exception) {
            QMessageBox::critical(this, "Error", QString::fromStdString(Exception.what()));
            return;
        }

        positionLineEdit->clear();
    });

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(positionLabel);
    layout->addWidget(positionLineEdit);
    layout->addWidget(deleteButton);

    QDialog* dialog = new QDialog;
    dialog->setLayout(layout);
    dialog->setWindowTitle("Delete Coat");
    dialog->exec();
    refreshTable();
}

void NewAdminWindow::updateCoat()
{
    QLabel* positionLabel = new QLabel("Position:");
    QLineEdit* positionLineEdit = new QLineEdit;
    QLabel* colourLabel = new QLabel("Colour:");
    QLineEdit* colourLineEdit = new QLineEdit;
    QLabel* sizeLabel = new QLabel("Size:");
    QLineEdit* sizeLineEdit = new QLineEdit;
    QLabel* priceLabel = new QLabel("Price:");
    QLineEdit* priceLineEdit = new QLineEdit;
    QLabel* quantityLabel = new QLabel("Quantity:");
    QLineEdit* quantityLineEdit = new QLineEdit;
    QLabel* photoLabel = new QLabel("Photo:");
    QLineEdit* photoLineEdit = new QLineEdit;

    QPushButton* updateButton = new QPushButton("Update Coat");

    connect(updateButton, &QPushButton::clicked, [=]() {
        int position = positionLineEdit->text().toInt();
        std::string colour = colourLineEdit->text().toStdString();
        std::string size = sizeLineEdit->text().toStdString();
        int price = priceLineEdit->text().toInt();
        int quantity = quantityLineEdit->text().toInt();
        std::string photo = photoLineEdit->text().toStdString();

        Coats coat = Coats(size, colour, price, quantity, photo);

        try {
            coat.validateCoat();
        }
        catch (const std::exception& Exception) {
            QMessageBox::critical(this, "Error", QString::fromStdString(Exception.what()));
            return;
        }

        try {
            this->commandManager.executeCommand(new UpdateCommand(this->service, position - 1, coat));
            this->service.updateCoat(position - 1, coat);
            QMessageBox::information(this, "Success", "Coat updated successfully!");
        }
        catch (const std::exception& Exception) {
            QMessageBox::critical(this, "Error", QString::fromStdString(Exception.what()));
            return;
        }

        positionLineEdit->clear();
        colourLineEdit->clear();
        sizeLineEdit->clear();
        priceLineEdit->clear();
        quantityLineEdit->clear();
        photoLineEdit->clear();
    });

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(positionLabel);
    layout->addWidget(positionLineEdit);
    layout->addWidget(colourLabel);
    layout->addWidget(colourLineEdit);
    layout->addWidget(sizeLabel);
    layout->addWidget(sizeLineEdit);
    layout->addWidget(priceLabel);
    layout->addWidget(priceLineEdit);
    layout->addWidget(quantityLabel);
    layout->addWidget(quantityLineEdit);
    layout->addWidget(photoLabel);
    layout->addWidget(photoLineEdit);
    layout->addWidget(updateButton);

    QDialog* dialog = new QDialog;
    dialog->setLayout(layout);
    dialog->setWindowTitle("Update Coat");
    dialog->exec();
    refreshTable();
}

NewUserWindow::NewUserWindow(Service& service, QWidget *parent) {
    this->service = service;
    QVBoxLayout *layout = new QVBoxLayout(this);
    // QLabel *titleLabel = new QLabel("User Window", this);
    // layout->addWidget(titleLabel);
    QVBoxLayout* files = new QVBoxLayout;
    QPushButton* html = new QPushButton("HTML");

    QPushButton* csv = new QPushButton("CSV");
    QLabel* fileTypeLabel = new QLabel("Choose file type:");
    files->addWidget(fileTypeLabel);
    files->addWidget(html);
    files->addWidget(csv);
    QDialog* dialog = new QDialog;
    connect(html, &QPushButton::clicked, [=]() {
        int index = 0;
        this->service.setFileType(index + 1);
        dialog->close();
    });
    connect(csv, &QPushButton::clicked, [=]() {
        int index = 1;
        this->service.setFileType(index + 1);
        dialog->close();
    });
    dialog->setLayout(files);
    dialog->setWindowTitle("File type");
    dialog->exec();

    if (this->service.getFileType() == 1)
        QMessageBox::information(this, "File Type", "You chose HTML.");
    else
        QMessageBox::information(this, "File Type", "You chose CSV.");

    QMessageBox::information(this, "Welcome", "Welcome to our online store!");

    QPushButton *shopButton = new QPushButton("Shop", this);
    layout->addWidget(shopButton);
    connect(shopButton, &QPushButton::clicked, this, &NewUserWindow::shop);
    QPushButton *seeShoppingBagButton = new QPushButton("See shopping bag", this);
    layout->addWidget(seeShoppingBagButton);
    connect(seeShoppingBagButton, &QPushButton::clicked, this, &NewUserWindow::seeShoppingBag);
    QPushButton *saveShoppingBagButton = new QPushButton("Save shopping bag", this);
    layout->addWidget(saveShoppingBagButton);
    connect(saveShoppingBagButton, &QPushButton::clicked, this, &NewUserWindow::saveShoppingBag);
    QPushButton *exitButton = new QPushButton("Exit", this);
    layout->addWidget(exitButton);
    connect(exitButton, &QPushButton::clicked, this, &QWidget::close);

    setWindowTitle("User Window");
    resize(400, 300);
}

void NewUserWindow::shop()
{
    QString choice = QInputDialog::getText(this, "Size Selection", "What size are you looking for?");

    std::vector<Coats> coats = this->service.getCoatsBySize(choice.toStdString());

    for (auto& coat : coats) {
        QString coatInfo = "Colour: " + QString::fromStdString(coat.getColour()) + "\n"
                           + "Size: " + QString::fromStdString(coat.getSize()) + "\n"
                           + "Price: " + QString::number(coat.getPrice()) + "\n"
                           + "Quantity: " + QString::number(coat.getQuantity()) + "\n"
                           + "Photo: " + QString::fromStdString(coat.getPhoto()) + "\n";
        QMessageBox msgBox;
        msgBox.setWindowTitle("Coat Information");
        msgBox.setText(coatInfo);
        msgBox.addButton("Add to Cart", QMessageBox::AcceptRole);
        msgBox.addButton("Exit", QMessageBox::RejectRole);

        msgBox.addButton("Next", QMessageBox::RejectRole);
        msgBox.setIcon(QMessageBox::Question);

        int choice = msgBox.exec();

        if (choice == QMessageBox::AcceptRole) {
            this->service.addToCart(coat);
            std::string totalInfo = "The coat has been added to your cart. Your current total is " + std::to_string(this->service.getTotal());
            QMessageBox::information(this, "Current Total", QString::fromStdString(totalInfo));
        } else if (choice == QMessageBox::RejectRole) {
            if (msgBox.clickedButton()->text() == "Next")
                continue;
            else
                break;
        }
    }
}

//void NewUserWindow::seeShoppingBag()
//{
//    std::vector<Coats> coats = this->service.getShoppingBag();
//
//    QTableWidget* tableWidget = new QTableWidget(coats.size(), 4);
//    tableWidget->setHorizontalHeaderLabels(QStringList() << "Size" << "Colour"  << "Price" << "Photo");
//    tableWidget->verticalHeader()->setVisible(false);
//
//    int row = 0;
//    for (auto coat : coats) {
//        tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(coat.getSize())));
//        tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(coat.getColour())));
//        tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(coat.getPrice())));
//        tableWidget->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(coat.getPhoto())));
//        row++;
//    }
//
//    tableWidget->resizeColumnsToContents();
//    tableWidget->resize(tableWidget->horizontalHeader()->length(), tableWidget->verticalHeader()->length());
//
//    tableWidget->show();
//}

void NewUserWindow::seeShoppingBag() {
    ShoppingBasketDialog dialog(service, this);
    dialog.exec();
}

void NewUserWindow::saveShoppingBag()
{
    QString filename = QInputDialog::getText(this, "Save Shopping Bag", "Enter the filename:");
    this->service.saveShoppingBag(filename.toStdString());
}