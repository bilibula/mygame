cmake_minimum_required(VERSION 3.21)
project(Age_of_Stone LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


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
            game.h
            game.cpp
            )
else()
    add_executable(${PROJECT_NAME}
            main.cpp
            mainwindow.cpp
            mainwindow.h
            mainwindow.ui
            icon.qrc
            board.h
            board.cpp
            board.h
            board.cpp
            game.h
            game.cpp
            )
endif()

target_link_libraries(${PROJECT_NAME}
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

