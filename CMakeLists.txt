#
# \file       CMakeLists.txt
# \author     GrandChris
# \date       2020-10-11
# \brief      Build the library
#

cmake_minimum_required(VERSION 3.16)

# # Include vcpkg as package manager
# set(CMAKE_TOOLCHAIN_FILE ./vcpkg/scripts/buildsystems/vcpkg.cmake
#   CACHE STRING "Vcpkg toolchain file")

# Create the project
project(ucppcoro)

# Export compile commands for VSCode C++ Intellisense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include directories
include_directories("./include")

# Add source files
file(GLOB SOURCE_FILES CONFIGURE_DEPENDS
    "./source/*.cpp"
)

# Add files to the executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Enable Coroutines
target_compile_options(${PROJECT_NAME} PRIVATE
  -fcoroutines 
  -Wall 
  -O3
)