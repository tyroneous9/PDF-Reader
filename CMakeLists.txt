cmake_minimum_required(VERSION 3.10)
project(CPP_PDF_Reader)

set(CMAKE_CXX_STANDARD 17)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Poppler REQUIRED)

add_executable(pdf_reader src/main.cpp)
target_include_directories(pdf_reader PRIVATE include)
target_link_libraries(pdf_reader Qt6::Widgets Poppler::Poppler)
