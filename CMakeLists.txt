#
# \file       CMakeLists.txt
# \author     GrandChris
# \date       2020-10-11
# \brief      Build the library
#

cmake_minimum_required(VERSION 3.16)

# Include vcpkg as package manager
set(CMAKE_TOOLCHAIN_FILE ./vcpkg/scripts/buildsystems/vcpkg.cmake
  CACHE STRING "Vcpkg toolchain file")

  ################################### Library ################################

# Create the project
project(ucppcoro)

# Export compile commands for VSCode C++ Intellisense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# Add executable
add_executable(${PROJECT_NAME})

# Add compile option
target_compile_options(${PROJECT_NAME} PRIVATE
  -fcoroutines 
  -Wall 
  -Og
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE "./include")

# Add source files
file(GLOB SOURCE_FILES CONFIGURE_DEPENDS
    "./source/*.cpp"
)
target_sources(${PROJECT_NAME} PRIVATE ${SOURCE_FILES})

################################### Unit Tests ################################

set(PROJECT_TEST_NAME ${PROJECT_NAME}_tests)

add_executable(${PROJECT_TEST_NAME})

# Add source files
file(GLOB SOURCE_FILES_TEST CONFIGURE_DEPENDS
    "./test/*.cpp"
)
target_sources(${PROJECT_TEST_NAME} PRIVATE ${SOURCE_FILES_TEST})

find_package(GTest CONFIG REQUIRED)

target_link_libraries(${PROJECT_TEST_NAME} PRIVATE GTest::gtest_main)

enable_testing()
include(GoogleTest)
gtest_discover_tests(${PROJECT_TEST_NAME})





