#include "ui/ui.h"
#include "gui/gui.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    GUI gui;
    gui.show();
    return app.exec();
//     UI ui;
//     ui.run();
//     return 0;
}