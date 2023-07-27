cmake_minimum_required(VERSION 3.5)

project(adc-converter VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include_directories(source)

set(PROJECT_SOURCES
    
    # General
    
    source/abstract_widget.h
    source/abstract_widget.cpp
    
    # MVC
    
    #source/mvc/model_attribute.h
    #source/mvc/view_element.h
    source/mvc/element_manager.h
    source/mvc/abstract_model.h
    source/mvc/abstract_view.h
    source/mvc/abstract_controller.h
    #source/mvc/model_attribute.cpp
    #source/mvc/view_element.cpp
    source/mvc/element_manager.cpp
    source/mvc/abstract_model.cpp
    source/mvc/abstract_view.cpp
    source/mvc/abstract_controller.cpp
    
    # Options (Widgets)
    
    source/options/bps/bps_model.h
    source/options/bps/bps_view.h
    source/options/bps/bps_controller.h
    source/options/bps/bps_widget.h
    source/options/bps/bps_model.cpp
    source/options/bps/bps_view.cpp
    source/options/bps/bps_controller.cpp
    source/options/bps/bps_widget.cpp
    
    # General
    
    source/main.cpp
    source/mainwindow.cpp
    source/mainwindow.h
    source/mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(adc-converter
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET adc-converter APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(adc-converter SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(adc-converter
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(adc-converter PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(adc-converter PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS adc-converter
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(adc-converter)
endif()
