cmake_minimum_required(VERSION 3.17)
project(Task2)

set(CMAKE_CXX_STANDARD 17)

# Tell cmake where Qt is located
set(Qt5_DIR "/Users/rinokus/Documents/Projects/CoDiM-management-tool/Src/venv/lib/python3.7/site-packages/PyQt5/Qt")

# Tell cmake to find the modules Qt5Core and Qt5widgets
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

add_executable(Task2 main.cpp xml_reader.h enterprise_division.h employee.h)

# Link the library to the executable
target_link_libraries(Task2 Qt5::Core Qt5::Widgets)