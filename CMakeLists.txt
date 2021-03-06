cmake_minimum_required(VERSION 2.8)

# options
option(BUILD_VERBOSE "verbose makefile build" OFF)


# main project name defined
project(jview)

# osx architectures
if(NOT BUILD_NEWGCC)
    set(CMAKE_OSX_ARCHITECTURES "x86_64")
endif()

# set default build to release
set(CMAKE_BUILD_TYPE Release)

# output directories
if(CMAKE_GENERATOR STREQUAL "Unix Makefiles")
    #set(BIN_DIR_SUFFIX mk)
    set(MAKEFILES ON)
    set(CMAKE_VERBOSE_MAKEFILE ${BUILD_VERBOSE})
elseif(CMAKE_GENERATOR STREQUAL "Xcode")
    #set(BIN_DIR_SUFFIX xcode)
    set(XCODE ON)
elseif(CMAKE_GENERATOR STREQUAL "Visual Studio 10 Win64")
	add_definitions(-D_SCL_SECURE_NO_WARNINGS)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif(CMAKE_GENERATOR STREQUAL "Unix Makefiles")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${BIN_DIR_SUFFIX})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${BIN_DIR_SUFFIX})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${BIN_DIR_SUFFIX})


GET_FILENAME_COMPONENT(COMMON_PATH "${NEAR_PATH}/common" ABSOLUTE)


#include directories
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(/usr/local/include)

if(WIN32)
    add_definitions(-DNOMINMAX)
endif()

if(WIN32)
    GET_FILENAME_COMPONENT(DEP_DIR "./OpenEXR/win" ABSOLUTE)
    include_directories(${DEP_DIR})
    include_directories(${DEP_DIR}/half)
    include_directories(${DEP_DIR}/Iex)
    include_directories(${DEP_DIR}/IlmImf)
    include_directories(${DEP_DIR}/IlmThread)
    include_directories(${DEP_DIR}/Imath)
    include_directories(${DEP_DIR}/zlib)
    link_directories(${DEP_DIR}/lib)
    SET(EXR_LIB half Iex IlmImf IlmThread Imath zlib)
else()
    find_package(ZLIB)
    GET_FILENAME_COMPONENT(DEP_DIR "./OpenEXR/" ABSOLUTE)
    include(${DEP_DIR}/FindOpenEXR.cmake)
    include_directories(${OPENEXR_INCLUDE_PATHS})
    SET(EXR_LIB ${OPENEXR_LIBRARIES})
endif()

add_subdirectory(src)

