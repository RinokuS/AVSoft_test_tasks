cmake_minimum_required(VERSION 3.17)
project(Task2)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)

# Tell cmake to find the modules Qt5Core and Qt5widgets
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

add_executable(Task2 main.cpp xml_reader.h enterprise_division.h employee.h tree_model.h views/main_window.h views/main_window.cpp views/division_editor.h views/division_editor.cpp views/employee_editor.h views/employee_editor.cpp)

# Link the library to the executable
target_link_libraries(Task2 Qt5::Core Qt5::Widgets)