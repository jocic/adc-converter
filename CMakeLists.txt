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
    
    #######
    # APP #
    #######
    
    # General
    
    source/app/app_icons.h
    source/app/app_icons.cpp
    source/app/app_mediator.h
    source/app/app_mediator.cpp
    source/app/file_manager.h
    source/app/file_manager.cpp
    source/app/file_loader.h
    source/app/file_loader.cpp
    source/app/file_saver.h
    source/app/file_saver.cpp
    
    # Converters
    
    source/app/converters/abstract_converter.h
    source/app/converters/abstract_converter.cpp
    source/app/converters/hexadecimal_converter.h
    source/app/converters/hexadecimal_converter.cpp
    source/app/converters/decimal_converter.h
    source/app/converters/decimal_converter.cpp
    
    # MVC
    
    source/app/mvc/element_manager.h
    source/app/mvc/element_manager.cpp
    source/app/mvc/abstract_model.h
    source/app/mvc/abstract_model.cpp
    source/app/mvc/abstract_view.h
    source/app/mvc/abstract_view.cpp
    source/app/mvc/abstract_controller.h
    source/app/mvc/abstract_controller.cpp
    
    # Workers
    
    source/app/workers/abstract_worker.h
    source/app/workers/abstract_worker.cpp
    source/app/workers/load_worker.h
    source/app/workers/load_worker.cpp
    source/app/workers/save_worker.h
    source/app/workers/save_worker.cpp
    
    ############
    # POPOVERS #
    ############
    
    source/popovers/abstract_popover.h
    source/popovers/abstract_popover.cpp
    
    # Processing
    
    source/popovers/processing/processing_model.h
    source/popovers/processing/processing_view.h
    source/popovers/processing/processing_controller.h
    source/popovers/processing/processing_popover.h
    source/popovers/processing/processing_model.cpp
    source/popovers/processing/processing_view.cpp
    source/popovers/processing/processing_controller.cpp
    source/popovers/processing/processing_popover.cpp
    
    ###################
    # VIEWS - SAMPLES #
    ###################
    
    source/views/samples/elements/hex_viewer.h
    source/views/samples/elements/hex_viewer.cpp
    source/views/samples/samples_model.h
    source/views/samples/samples_view.h
    source/views/samples/samples_controller.h
    source/views/samples/samples_widget.h
    source/views/samples/samples_model.cpp
    source/views/samples/samples_view.cpp
    source/views/samples/samples_controller.cpp
    source/views/samples/samples_widget.cpp
    
    #####################
    # WIDGETS - OPTIONS #
    #####################
    
    # Options (Stream)
    
    source/widgets/options/stream/stream_model.h
    source/widgets/options/stream/stream_view.h
    source/widgets/options/stream/stream_controller.h
    source/widgets/options/stream/stream_widget.h
    source/widgets/options/stream/stream_model.cpp
    source/widgets/options/stream/stream_view.cpp
    source/widgets/options/stream/stream_controller.cpp
    source/widgets/options/stream/stream_widget.cpp
    
    # Options (Reference)
    
    source/widgets/options/reference/reference_model.h
    source/widgets/options/reference/reference_view.h
    source/widgets/options/reference/reference_controller.h
    source/widgets/options/reference/reference_widget.h
    source/widgets/options/reference/reference_model.cpp
    source/widgets/options/reference/reference_view.cpp
    source/widgets/options/reference/reference_controller.cpp
    source/widgets/options/reference/reference_widget.cpp
    
    # Options (Serial)
    
    source/widgets/options/serial/serial_model.h
    source/widgets/options/serial/serial_view.h
    source/widgets/options/serial/serial_controller.h
    source/widgets/options/serial/serial_widget.h
    source/widgets/options/serial/serial_model.cpp
    source/widgets/options/serial/serial_view.cpp
    source/widgets/options/serial/serial_controller.cpp
    source/widgets/options/serial/serial_widget.cpp
    
    # Options (Communication)
    
    source/widgets/options/communication/communication_model.h
    source/widgets/options/communication/communication_view.h
    source/widgets/options/communication/communication_controller.h
    source/widgets/options/communication/communication_widget.h
    source/widgets/options/communication/communication_model.cpp
    source/widgets/options/communication/communication_view.cpp
    source/widgets/options/communication/communication_controller.cpp
    source/widgets/options/communication/communication_widget.cpp
    
    ###################
    # WIDGETS - TOOLS #
    ###################
    
    # Tools (Playback)
    
    source/widgets/tools/playback/playback_model.h
    source/widgets/tools/playback/playback_view.h
    source/widgets/tools/playback/playback_controller.h
    source/widgets/tools/playback/playback_widget.h
    source/widgets/tools/playback/playback_model.cpp
    source/widgets/tools/playback/playback_view.cpp
    source/widgets/tools/playback/playback_controller.cpp
    source/widgets/tools/playback/playback_widget.cpp
    
    # Tools (Hex Converter)
    
    source/widgets/tools/hexadecimal-converter/hexadecimal_model.h
    source/widgets/tools/hexadecimal-converter/hexadecimal_view.h
    source/widgets/tools/hexadecimal-converter/hexadecimal_controller.h
    source/widgets/tools/hexadecimal-converter/hexadecimal_widget.h
    source/widgets/tools/hexadecimal-converter/hexadecimal_model.cpp
    source/widgets/tools/hexadecimal-converter/hexadecimal_view.cpp
    source/widgets/tools/hexadecimal-converter/hexadecimal_controller.cpp
    source/widgets/tools/hexadecimal-converter/hexadecimal_widget.cpp
    
    # Tools (Dec Converter)
    
    source/widgets/tools/decimal-converter/decimal_model.h
    source/widgets/tools/decimal-converter/decimal_view.h
    source/widgets/tools/decimal-converter/decimal_controller.h
    source/widgets/tools/decimal-converter/decimal_widget.h
    source/widgets/tools/decimal-converter/decimal_model.cpp
    source/widgets/tools/decimal-converter/decimal_view.cpp
    source/widgets/tools/decimal-converter/decimal_controller.cpp
    source/widgets/tools/decimal-converter/decimal_widget.cpp
    
    ##################
    # WIDGETS - INFO #
    ##################
    
    # Info (General)
    
    source/widgets/info/general/general_model.h
    source/widgets/info/general/general_view.h
    source/widgets/info/general/general_controller.h
    source/widgets/info/general/general_widget.h
    source/widgets/info/general/general_model.cpp
    source/widgets/info/general/general_view.cpp
    source/widgets/info/general/general_controller.cpp
    source/widgets/info/general/general_widget.cpp
    
    # General
    
    source/main.cpp
    
    source/mainwindow.h
    source/mainwindow.cpp
    source/mainwindow.ui
    
    source/widgets/abstract_widget.h
    source/widgets/abstract_widget.cpp
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
