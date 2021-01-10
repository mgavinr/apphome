cmake_minimum_required(VERSION 3.17)
project(gnomehw)

# CMAKE SETTINGS
# --------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_INSTALL_RPATH "")
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
SET(CMAKE_EXE_LINKER_FLAGS "-Wl,--disable-new-dtags")

# COMMON SETTINGS
# ---------------
if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else()
    message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif()

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-4.0)

# PROJECT SETTINGS
# ----------------
link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})
add_executable(gnomehw main.cpp myUtils.cpp myUtils.h myGnomeWindow.cpp myGnomeWindow.h myGnomeApplication.cpp myGnomeApplication.h myGnomeMenuApplication.cpp myGnomeMenuApplication.h)
target_link_libraries(gnomehw ${GTKMM_LIBRARIES} lidebug)
