cmake_minimum_required(VERSION 3.10)
project(MySDL3App C)

# Enable exporting compile commands for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find pkg-config and SDL3 using it
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL3 REQUIRED sdl3)

add_executable(app src/main.c)

# Include SDL3 headers
target_include_directories(app PRIVATE ${SDL3_INCLUDE_DIRS})

# Add SDL3 compiler flags
target_compile_options(app PRIVATE ${SDL3_CFLAGS_OTHER})

# Add your own compile flags matching Makefile
target_compile_options(app PRIVATE -std=c11 -Wall -Wextra -O2)

# Link SDL3 libraries found by pkg-config
target_link_libraries(app PRIVATE ${SDL3_LIBRARIES})
