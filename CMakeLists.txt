
cmake_minimum_required(VERSION 3.1)

project(MeadowsECS)

option(BUILD_TEST "Build the MeadowsECS unit tests" OFF)

set(SOURCE_FILES src/Entity.cpp src/World.cpp src/ComponentRegistry.cpp src/System.cpp src/BitSet.cpp src/ComponentSet.cpp)
set(HEADER_FILES include/MeadowsECS/Entity.h include/MeadowsECS/System.h include/MeadowsECS/World.h
        include/MeadowsECS/Component.h include/MeadowsECS/ComponentSet.h include/MeadowsECS/ComponentRegistry.h
        include/MeadowsECS/BitSet.h)

# Also add header files 
add_library(MeadowsECS ${SOURCE_FILES} ${HEADER_FILES})

set_property(TARGET MeadowsECS PROPERTY CXX_STANDARD 14)
target_include_directories(MeadowsECS PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/MeadowsECS>
        $<INSTALL_INTERFACE:include/MeadowsECS>)

if (BUILD_TEST)
    add_subdirectory(test)
endif ()