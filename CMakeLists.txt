cmake_minimum_required(VERSION 3.10)
project(PDFReader)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Poppler REQUIRED)

add_executable(PDFReader main.cpp)

target_link_libraries(PDFReader Qt6::Widgets Poppler::Poppler)
