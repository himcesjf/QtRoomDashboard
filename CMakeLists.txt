cmake_minimum_required(VERSION 3.16)

project(QtRoomDashboard VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Qml Quick QuickControls2)
find_package(PkgConfig REQUIRED)
pkg_check_modules(SPDLOG REQUIRED spdlog)

qt6_standard_project_setup()

# Add executable
qt6_add_executable(QtRoomDashboard
    main.cpp
    SensorModel.cpp
    SensorModel.h
    CsvWriter.cpp
    CsvWriter.h
    SensorWorker.cpp
    SensorWorker.h
)

# Add QML module
qt6_add_qml_module(QtRoomDashboard
    URI QtRoomDashboard
    VERSION 1.0
    QML_FILES main.qml
)

# Link libraries
target_link_libraries(QtRoomDashboard PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickControls2
    ${SPDLOG_LIBRARIES}
)

# Include directories
target_include_directories(QtRoomDashboard PRIVATE ${SPDLOG_INCLUDE_DIRS})
target_compile_options(QtRoomDashboard PRIVATE ${SPDLOG_CFLAGS_OTHER}) 