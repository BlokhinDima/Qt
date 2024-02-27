cmake_minimum_required(VERSION 3.5)

project(Task1 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Concurrent Charts)


set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        datachart.h
        datachart.cpp
        chartwindow.h
        chartwindow.cpp
        chartwindow.ui
)


add_executable(Task1
    ${PROJECT_SOURCES}
)


target_link_libraries(Task1 Qt6::Widgets
                            Qt6::Concurrent
                            Qt6::Charts
)


