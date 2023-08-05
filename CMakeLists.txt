cmake_minimum_required(VERSION 3.5)

project(adc-converter VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

FILE(COPY assets/icons DESTINATION ${CMAKE_BINARY_DIR})

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS SerialPort)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS SerialPort)

add_subdirectory(libraries/c89-wav)
include_directories(${C89_WAV_DIR})

include_directories(source)

set(PROJECT_SOURCES
    
    # General
    
    source/app_icons.h
    source/app_icons.cpp
    
    source/main.cpp
    
    source/mainwindow.cpp
    source/mainwindow.h
    source/mainwindow.ui
    
    source/widgets/abstract_widget.h
    source/widgets/abstract_widget.cpp
    
    # MVC
    
    source/mvc/element_manager.h
    source/mvc/abstract_model.h
    source/mvc/abstract_view.h
    source/mvc/abstract_controller.h
    source/mvc/element_manager.cpp
    source/mvc/abstract_model.cpp
    source/mvc/abstract_view.cpp
    source/mvc/abstract_controller.cpp
    
    # Converters
    
    source/converters/abstract_converter.h
    source/converters/abstract_converter.cpp
    source/converters/hex_converter.h
    source/converters/hex_converter.cpp
    source/converters/dec_converter.h
    source/converters/dec_converter.cpp
    
    #####################
    # WIDGETS - OPTIONS #
    #####################
    
    # Options (Samples)
    
    source/widgets/options/samples/smp_model.h
    source/widgets/options/samples/smp_view.h
    source/widgets/options/samples/smp_controller.h
    source/widgets/options/samples/smp_widget.h
    source/widgets/options/samples/smp_model.cpp
    source/widgets/options/samples/smp_view.cpp
    source/widgets/options/samples/smp_controller.cpp
    source/widgets/options/samples/smp_widget.cpp
    
    # Options (Reference)
    
    source/widgets/options/reference/ref_model.h
    source/widgets/options/reference/ref_view.h
    source/widgets/options/reference/ref_controller.h
    source/widgets/options/reference/ref_widget.h
    source/widgets/options/reference/ref_model.cpp
    source/widgets/options/reference/ref_view.cpp
    source/widgets/options/reference/ref_controller.cpp
    source/widgets/options/reference/ref_widget.cpp
    
    # Options (Serial)
    
    source/widgets/options/serial/ser_model.h
    source/widgets/options/serial/ser_view.h
    source/widgets/options/serial/ser_controller.h
    source/widgets/options/serial/ser_widget.h
    source/widgets/options/serial/ser_model.cpp
    source/widgets/options/serial/ser_view.cpp
    source/widgets/options/serial/ser_controller.cpp
    source/widgets/options/serial/ser_widget.cpp
    
    # Options (Communication)
    
    source/widgets/options/communication/com_model.h
    source/widgets/options/communication/com_view.h
    source/widgets/options/communication/com_controller.h
    source/widgets/options/communication/com_widget.h
    source/widgets/options/communication/com_model.cpp
    source/widgets/options/communication/com_view.cpp
    source/widgets/options/communication/com_controller.cpp
    source/widgets/options/communication/com_widget.cpp
    
    ###################
    # WIDGETS - TOOLS #
    ###################
    
    # Tools (Playback)
    
    source/widgets/tools/playback/pl_model.h
    source/widgets/tools/playback/pl_view.h
    source/widgets/tools/playback/pl_widget.h
    source/widgets/tools/playback/pl_model.cpp
    source/widgets/tools/playback/pl_view.cpp
    source/widgets/tools/playback/pl_widget.cpp
    
    # Tools (Hex Converter)
    
    source/widgets/tools/hex-converter/hex_model.h
    source/widgets/tools/hex-converter/hex_view.h
    source/widgets/tools/hex-converter/hex_controller.h
    source/widgets/tools/hex-converter/hex_widget.h
    source/widgets/tools/hex-converter/hex_model.cpp
    source/widgets/tools/hex-converter/hex_view.cpp
    source/widgets/tools/hex-converter/hex_controller.cpp
    source/widgets/tools/hex-converter/hex_widget.cpp
    
    # Tools (Dec Converter)
    
    source/widgets/tools/dec-converter/dec_model.h
    source/widgets/tools/dec-converter/dec_view.h
    source/widgets/tools/dec-converter/dec_controller.h
    source/widgets/tools/dec-converter/dec_widget.h
    source/widgets/tools/dec-converter/dec_model.cpp
    source/widgets/tools/dec-converter/dec_view.cpp
    source/widgets/tools/dec-converter/dec_controller.cpp
    source/widgets/tools/dec-converter/dec_widget.cpp
    
    ##################
    # WIDGETS - INFO #
    ##################
    
    # Info (General)
    
    source/widgets/info/general/gen_model.h
    source/widgets/info/general/gen_view.h
    source/widgets/info/general/gen_controller.h
    source/widgets/info/general/gen_widget.h
    source/widgets/info/general/gen_model.cpp
    source/widgets/info/general/gen_view.cpp
    source/widgets/info/general/gen_controller.cpp
    source/widgets/info/general/gen_widget.cpp
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

target_link_libraries(adc-converter PRIVATE
    c89-wav
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::SerialPort)

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
