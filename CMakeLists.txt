# Check minimum required CMake version
cmake_minimum_required(VERSION 3.9)

project("plot")

if (WIN32)
    set(FUCK_THE_WIN WIN32)
endif()

set(SOURCES
    src/main.cpp
    src/workers.cpp
    src/vm.cpp
    )

set(HEADERS
    include/workers.h
    include/vm.h
    )

set(QML_SOURCES
    qml/main.qml
    )

find_package(Qt5 COMPONENTS Core Qml Quick REQUIRED)
qt5_add_resources(QT_RESOURCES qml/qml_resources.qrc)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${QML_SOURCES} ${QT_RESOURCES} ${FUCK_THE_WIN})

target_compile_definitions(${PROJECT_NAME} PRIVATE ${QtQml_DEFINITIONS})

set_target_properties(${PROJECT_NAME} PROPERTIES AUTOMOC ON)
set_target_properties(${PROJECT_NAME} PROPERTIES AUTOUIC ON)
set_target_properties(${PROJECT_NAME} PROPERTIES AUTOMOC ON)
set_target_properties(${PROJECT_NAME} PROPERTIES CMAKE_CXX_STANDARD 14)
set_target_properties(${PROJECT_NAME} PROPERTIES CMAKE_CXX_EXTENSIONS OFF)
set_target_properties(${PROJECT_NAME} PROPERTIES CMAKE_INCLUDE_CURRENT_DIR ON)
set_target_properties(${PROJECT_NAME} PROPERTIES CMAKE_CXX_STANDARD_REQUIRED ON)

target_compile_options(
    ${PROJECT_NAME}
    PUBLIC -Wall
    PUBLIC -Wextra
    PUBLIC -Werror
    )

target_link_libraries(
    ${PROJECT_NAME}
    Qt5::Core
    Qt5::Qml
    Qt5::Quick
    )

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_14)

target_include_directories(${PROJECT_NAME} PUBLIC ./include)
target_include_directories(${PROJECT_NAME} PRIVATE ${QtQml_INCLUDE_DIRECTORY})
