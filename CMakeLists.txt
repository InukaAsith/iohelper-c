cmake_minimum_required(VERSION 3.10)
project(iohelper VERSION 1.0.0 DESCRIPTION "Simple IO helper library for C")

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Create library
add_library(iohelper SHARED
    src/iohelper.c
)

# Set library properties
set_target_properties(iohelper PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER src/iohelper.h
)

# Set include directories
target_include_directories(iohelper PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Install library
include(GNUInstallDirs)
install(TARGETS iohelper
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/iohelper
)

# Generate and install pkg-config file
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/iohelper.pc.in
    ${CMAKE_CURRENT_BINARY_DIR}/iohelper.pc
    @ONLY
)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/iohelper.pc
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)