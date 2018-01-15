
project(MeadowsECSTest)

include(cmake/ParseAndAddCatchTests.cmake)

set(SOURCE_FILES src/TestMain.cpp src/BitsetTest.cpp src/ComponentRegistryTest.cpp src/WorldTest.cpp
        src/SystemTest.cpp)
add_executable(MeadowsECSTest ${SOURCE_FILES})
target_link_libraries(MeadowsECSTest PUBLIC MeadowsECS)
set_property(TARGET MeadowsECSTest PROPERTY CXX_STANDARD 14)

target_include_directories(MeadowsECSTest PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

enable_testing()
ParseAndAddCatchTests(MeadowsECSTest)