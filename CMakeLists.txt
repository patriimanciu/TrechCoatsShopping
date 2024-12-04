cmake_minimum_required(VERSION 3.26)
project(TrenchCoatsShopping)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

include_directories(domain)
include_directories(repository)
include_directories(service)
include_directories(ui)

add_executable(TrenchCoatsShopping
        domain/TrenchCoats.cpp
        domain/TrenchCoats.h
        repository/repository.cpp
        repository/repository.h
        service/service.cpp
        service/service.h
        ui/ui.cpp
        ui/ui.h
        main.cpp
        file/File.cpp
        file/File.h
        file/CSVFile.cpp
        file/CSVFile.h
        file/HTMLFile.cpp
        file/HTMLFile.h
        gui/gui.cpp
        gui/gui.h
        gui/shoppingBasket.h
        gui/dialog.h
        gui/commandManager.h
        gui/command.h
)

target_link_libraries(TrenchCoatsShopping
        Qt::Core
        Qt::Gui
        Qt::Widgets
)