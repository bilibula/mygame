cmake_minimum_required(VERSION 3.19)
project(mygame LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER '~/CLionProjects/mygame/Age_of_Stone')

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)



if(ANDROID)
    add_library(${PROJECT_NAME} SHARED
            main.cpp
            mainwindow.cpp
            mainwindow.h
            mainwindow.ui
            icon.qrc
            board.h
            board.cpp
            card.h
            card.cpp
            interfunc.h
            interfunc.cpp
            game.h
            game.cpp
            )
else()
    add_executable(${PROJECT_NAME}/Age_of_Stone/
            main.cpp
            mainwindow.cpp
            mainwindow.h
            mainwindow.ui
            icon.qrc
            board.h
            board.cpp
            card.h
            card.cpp
            game.h
            game.cpp
            )
endif()

target_link_libraries(${PROJECT_NAME}
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

