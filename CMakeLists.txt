cmake_minimum_required(VERSION 3.16)
project(KiraOtoToolbox VERSION 1.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Core5Compat Gui Widgets Concurrent Network Qml Svg LinguistTools PrintSupport)

include(GNUInstallDirs)

qt_standard_project_setup(
    I18N_SOURCE_LANGUAGE en
    I18N_TRANSLATED_LANGUAGES zh_CN ja
)

add_subdirectory(src)

option(KIRAOTOTOOLBOX_BUILD_TESTING "Build KiraOtoToolbox tests" OFF)
if(KIRAOTOTOOLBOX_BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
