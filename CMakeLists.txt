cmake_minimum_required(VERSION 3.0)

project(Calculator)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    "${PROJECT_SOURCE_DIR}/main.cpp"
    "${PROJECT_SOURCE_DIR}/src/button.cpp"
    "${PROJECT_SOURCE_DIR}/src/calculator.cpp"
    "${PROJECT_SOURCE_DIR}/src/inputbar.cpp"
    "${PROJECT_SOURCE_DIR}/src/net.cpp"
    "${PROJECT_SOURCE_DIR}/src/operator.cpp"
)

set(HEADERS
    "${PROJECT_SOURCE_DIR}/src/button.h"
    "${PROJECT_SOURCE_DIR}/src/calculator.h"
    "${PROJECT_SOURCE_DIR}/src/inputbar.h"
    "${PROJECT_SOURCE_DIR}/src/net.h"
    "${PROJECT_SOURCE_DIR}/src/operator.h"
)

include_directories("${PROJECT_SOURCE_DIR}/src")

set(Calculator_RESOURCE_LOC "\"${PROJECT_SOURCE_DIR}/resource\"")

configure_file(Config.h.in "${PROJECT_SOURCE_DIR}/src/Config.h")

set(SFML_STATIC_LIBRARIES True)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
else()
    message("\nSFML directory not found. Please specify the correct SFML directory using -DSFML_DIR=<directory> option\n")
endif()

add_executable(Calculator ${SOURCES} ${HEADERS})
target_link_libraries(Calculator sfml-graphics sfml-window sfml-system)