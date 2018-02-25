
cmake_minimum_required(VERSION 3.1)

include(CheckCXXSourceCompiles)
include(CheckTypeSize)

project(MeadowsECS)

option(BUILD_TEST "Build the MeadowsECS unit tests" OFF)
option(CODE_COVERAGE "Build the library with gcov enabled" OFF)
option(USE_POPCOUNT_INTRINSIC "Use a compiler popcount intrinsic when available" ON)

# Check if a builtin popcount implementation exists and can be used
file(READ cmake/test_gcc_popcount.cpp GCC_POPCOUNT_SOURCE)
file(READ cmake/test_msvc_popcount.cpp MSVC_POPCOUNT_SOURCE)
check_cxx_source_compiles("${GCC_POPCOUNT_SOURCE}" GCC_POPCOUNT_EXISTS)
check_cxx_source_compiles("${MSVC_POPCOUNT_SOURCE}" MSVC_POPCOUNT_EXISTS)
check_type_size("unsigned int" SIZEOF_UNSIGNED_INT)

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

if (CODE_COVERAGE)
    if (NOT ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
        message(SEND_ERROR "Code coverage only supported on gcc")
    endif()
    target_compile_options(MeadowsECS PUBLIC "--coverage")
    target_link_libraries(MeadowsECS "--coverage")
endif()

# intrinsic popcounts can only be used with `unsigned int`, since internally `uint32_t` is used, these need to match
if (USE_POPCOUNT_INTRINSIC AND SIZEOF_UNSIGNED_INT EQUAL 4)
    if (GCC_POPCOUNT_EXISTS)
        target_compile_definitions(MeadowsECS PRIVATE USE_GCC_POPCOUNT)
    elseif(MSVC_POPCOUNT_EXISTS)
        # When this is used, the popcnt instruction must be supported by the CPU
        target_compile_definitions(MeadowsECS PRIVATE USE_MSVC_POPCOUNT)
    endif()
endif()

if (BUILD_TEST)
    add_subdirectory(test)
endif ()