cmake_minimum_required(VERSION 3.14)

project(Task1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(Task1
  main.cpp
)

target_link_libraries(Task1 Qt${QT_VERSION_MAJOR}::Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Network)
target_link_libraries(Task1 Qt${QT_VERSION_MAJOR}::Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Sql)
target_link_libraries(Task1 Qt${QT_VERSION_MAJOR}::Sql)

install(TARGETS Task1
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
