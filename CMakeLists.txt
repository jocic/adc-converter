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

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Charts)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Charts)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Multimedia)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Multimedia)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS SerialPort)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS SerialPort)

include_directories(source)

set(PROJECT_HEADERS
    
    #######
    # APP #
    #######
    
    # General
    
    source/app/app_types.h
    source/app/app_core.h
    source/app/app_icons.h
    source/app/app_transceiver.h
    source/app/app_mediator.h
    source/app/app_io.h
    source/app/app_loader.h
    source/app/app_saver.h
    source/app/app_exporter.h
    
    # Data
    
    source/app/data/data_receiver.h
    source/app/data/data_processor.h
    source/app/data/text_processor.h
    source/app/data/binary_processor.h
    
    # Converters
    
    source/app/converters/abstract_converter.h
    source/app/converters/hexadecimal_converter.h
    source/app/converters/decimal_converter.h
    
    # MVC
    
    source/app/mvc/element_manager.h
    source/app/mvc/abstract_model.h
    source/app/mvc/abstract_view.h
    source/app/mvc/abstract_controller.h
    
    # Workers
    
    source/app/workers/abstract_worker.h
    source/app/workers/abstract_file_worker.h
    source/app/workers/load_worker.h
    source/app/workers/save_worker.h
    source/app/workers/export_worker.h
    source/app/workers/play_worker.h
    
    # Audio
    
    source/app/audio/audio_source.h
    
    ############
    # POPOVERS #
    ############
    
    # General
    
    source/popovers/abstract_popover.h
    
    # About
    
    source/popovers/about/about_view.h
    source/popovers/about/about_popover.h
    
    # Processing
    
    source/popovers/processing/processing_model.h
    source/popovers/processing/processing_view.h
    source/popovers/processing/processing_controller.h
    source/popovers/processing/processing_popover.h
    
    #########
    # VIEWS #
    #########
    
    # Scope
    
    source/views/scope/elements/custom_chart_view.h
    source/views/scope/scope_view.h
    source/views/scope/scope_controller.h
    source/views/scope/scope_widget.h
    
    # Samples
    
    source/views/samples/elements/hex_viewer.h
    source/views/samples/samples_model.h
    source/views/samples/samples_view.h
    source/views/samples/samples_controller.h
    source/views/samples/samples_widget.h
    
    ###########
    # WIDGETS #
    ###########
    
    # General
    
    source/widgets/abstract_widget.h
    
    # Options (Stream)
    
    source/widgets/options/stream/stream_model.h
    source/widgets/options/stream/stream_view.h
    source/widgets/options/stream/stream_controller.h
    source/widgets/options/stream/stream_widget.h
    
    # Options (Reference)
    
    source/widgets/options/reference/reference_model.h
    source/widgets/options/reference/reference_view.h
    source/widgets/options/reference/reference_controller.h
    source/widgets/options/reference/reference_widget.h
    
    # Options (Serial)
    
    source/widgets/options/serial/serial_model.h
    source/widgets/options/serial/serial_view.h
    source/widgets/options/serial/serial_controller.h
    source/widgets/options/serial/serial_widget.h
    
    # Options (Communication)
    
    source/widgets/options/communication/communication_model.h
    source/widgets/options/communication/communication_view.h
    source/widgets/options/communication/communication_controller.h
    source/widgets/options/communication/communication_widget.h
    
    # Options (Controls)
    
    source/widgets/options/controls/controls_model.h
    source/widgets/options/controls/controls_view.h
    source/widgets/options/controls/controls_controller.h
    source/widgets/options/controls/controls_widget.h
    
    # Tools (Playback)
    
    source/widgets/tools/playback/playback_model.h
    source/widgets/tools/playback/playback_view.h
    source/widgets/tools/playback/playback_controller.h
    source/widgets/tools/playback/playback_widget.h
    
    # Tools (Hex Converter)
    
    source/widgets/tools/hexadecimal-converter/hexadecimal_model.h
    source/widgets/tools/hexadecimal-converter/hexadecimal_view.h
    source/widgets/tools/hexadecimal-converter/hexadecimal_controller.h
    source/widgets/tools/hexadecimal-converter/hexadecimal_widget.h
    
    # Tools (Dec Converter)
    
    source/widgets/tools/decimal-converter/decimal_model.h
    source/widgets/tools/decimal-converter/decimal_view.h
    source/widgets/tools/decimal-converter/decimal_controller.h
    source/widgets/tools/decimal-converter/decimal_widget.h
    
    # Info (General)
    
    source/widgets/info/general/general_model.h
    source/widgets/info/general/general_view.h
    source/widgets/info/general/general_controller.h
    source/widgets/info/general/general_widget.h
    
)

set(PROJECT_SOURCES
    
    #######
    # APP #
    #######
    
    # General
    
    source/app/app_core.cpp
    source/app/app_icons.cpp
    source/app/app_mediator.cpp
    source/app/app_transceiver.cpp
    source/app/app_io.cpp
    source/app/app_loader.cpp
    source/app/app_saver.cpp
    source/app/app_exporter.cpp
    
    # Data
    
    source/app/data/data_receiver.cpp
    source/app/data/data_processor.cpp
    source/app/data/text_processor.cpp
    source/app/data/binary_processor.cpp
    
    # Converters
    
    source/app/converters/abstract_converter.cpp
    source/app/converters/hexadecimal_converter.cpp
    source/app/converters/decimal_converter.cpp
    
    # MVC
    
    source/app/mvc/element_manager.cpp
    source/app/mvc/abstract_model.cpp
    source/app/mvc/abstract_view.cpp
    source/app/mvc/abstract_controller.cpp
    
    # Workers
    
    source/app/workers/abstract_worker.cpp
    source/app/workers/abstract_file_worker.cpp
    source/app/workers/load_worker.cpp
    source/app/workers/save_worker.cpp
    source/app/workers/export_worker.cpp
    source/app/workers/play_worker.cpp
    
    # Audio
    
    source/app/audio/audio_source.cpp
    
    ############
    # POPOVERS #
    ############
    
    # General
    
    source/popovers/abstract_popover.cpp
    
    # About
    
    source/popovers/about/about_view.cpp
    source/popovers/about/about_popover.cpp
    
    # Processing
    
    source/popovers/processing/processing_model.cpp
    source/popovers/processing/processing_view.cpp
    source/popovers/processing/processing_controller.cpp
    source/popovers/processing/processing_popover.cpp
    
    #########
    # VIEWS #
    #########
    
    # Scope
    
    source/views/scope/elements/custom_chart_view.cpp
    source/views/scope/scope_view.cpp
    source/views/scope/scope_controller.cpp
    source/views/scope/scope_widget.cpp
    
    # Samples
    
    source/views/samples/elements/hex_viewer.cpp
    source/views/samples/samples_model.cpp
    source/views/samples/samples_view.cpp
    source/views/samples/samples_controller.cpp
    source/views/samples/samples_widget.cpp
    
    ###########
    # WIDGETS #
    ###########
    
    # General
    
    source/widgets/abstract_widget.cpp
    
    # Options (Stream)
    
    source/widgets/options/stream/stream_model.cpp
    source/widgets/options/stream/stream_view.cpp
    source/widgets/options/stream/stream_controller.cpp
    source/widgets/options/stream/stream_widget.cpp
    
    # Options (Reference)
    
    source/widgets/options/reference/reference_model.cpp
    source/widgets/options/reference/reference_view.cpp
    source/widgets/options/reference/reference_controller.cpp
    source/widgets/options/reference/reference_widget.cpp
    
    # Options (Serial)
    
    source/widgets/options/serial/serial_model.cpp
    source/widgets/options/serial/serial_view.cpp
    source/widgets/options/serial/serial_controller.cpp
    source/widgets/options/serial/serial_widget.cpp
    
    # Options (Communication)
    
    source/widgets/options/communication/communication_model.cpp
    source/widgets/options/communication/communication_view.cpp
    source/widgets/options/communication/communication_controller.cpp
    source/widgets/options/communication/communication_widget.cpp
    
    # Options (Controls)
    
    source/widgets/options/controls/controls_model.cpp
    source/widgets/options/controls/controls_view.cpp
    source/widgets/options/controls/controls_controller.cpp
    source/widgets/options/controls/controls_widget.cpp
    
    # Tools (Playback)
    
    source/widgets/tools/playback/playback_model.cpp
    source/widgets/tools/playback/playback_view.cpp
    source/widgets/tools/playback/playback_controller.cpp
    source/widgets/tools/playback/playback_widget.cpp
    
    # Tools (Hex Converter)
    
    source/widgets/tools/hexadecimal-converter/hexadecimal_model.cpp
    source/widgets/tools/hexadecimal-converter/hexadecimal_view.cpp
    source/widgets/tools/hexadecimal-converter/hexadecimal_controller.cpp
    source/widgets/tools/hexadecimal-converter/hexadecimal_widget.cpp
    
    # Tools (Dec Converter)
    
    source/widgets/tools/decimal-converter/decimal_model.cpp
    source/widgets/tools/decimal-converter/decimal_view.cpp
    source/widgets/tools/decimal-converter/decimal_controller.cpp
    source/widgets/tools/decimal-converter/decimal_widget.cpp
    
    # Info (General)
    
    source/widgets/info/general/general_model.cpp
    source/widgets/info/general/general_view.cpp
    source/widgets/info/general/general_controller.cpp
    source/widgets/info/general/general_widget.cpp
    
    ###########
    # GENERAL #
    ###########
    
    source/mainwindow.h
    source/mainwindow.cpp
    source/mainwindow.ui
    
    source/main.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(adc-converter
        MANUAL_FINALIZATION
        ${PROJECT_HEADERS} ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET adc-converter APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(adc-converter SHARED
            ${PROJECT_HEADERS} ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(adc-converter
            ${PROJECT_HEADERS} ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(adc-converter PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Multimedia
    Qt${QT_VERSION_MAJOR}::Charts
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
