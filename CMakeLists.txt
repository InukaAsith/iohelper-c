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
if(WIN32 AND MINGW)
    # MinGW-specific installation paths
    install(TARGETS iohelper
        RUNTIME DESTINATION "${MINGW_PREFIX}/bin"
        LIBRARY DESTINATION "${MINGW_PREFIX}/lib"
        PUBLIC_HEADER DESTINATION "${MINGW_PREFIX}/include/iohelper"
    )
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/iohelper.pc
        DESTINATION "${MINGW_PREFIX}/lib/pkgconfig"
    )
else()
    # Standard installation paths for other platforms
    install(TARGETS iohelper
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/iohelper
    )
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/iohelper.pc
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
    )
endif()
