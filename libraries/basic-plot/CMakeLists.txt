cmake_minimum_required(VERSION 3.5)

project(basic-plot LANGUAGES CXX)

include_directories(source)

set(BASIC_PLOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/" PARENT_SCOPE)

file(COPY assets/test-files DESTINATION ${CMAKE_BINARY_DIR})

add_library(basic-plot
    source/basic_plot.h
    source/basic_plot.cpp
)

set_property(TARGET basic-plot)
