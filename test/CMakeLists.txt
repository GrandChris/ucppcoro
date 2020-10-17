#
# \file       CMakeLists.txt
# \author     GrandChris
# \date       2020-10-11
# \brief      Build the unit tests
#

cmake_minimum_required(VERSION 3.17 CXX)

# Include vcpkg as package manager
# set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg-master/scripts/buildsystems/vcpkg.cmake
#   CACHE STRING "Vcpkg toolchain file")

# Create the project
project(ucppcoro)

# Export compile commands for VSCode C++ Intellisense
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include directories
# include_directories("./include")

# Add source files
# file(GLOB SOURCE_FILES CONFIGURE_DEPENDS
#     "source/*.cpp"
# )

# Add files to the executable
add_executable(${PROJECT_NAME} "source/main.cpp")
