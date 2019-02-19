cmake_minimum_required(VERSION 3.5)
project(GfxHelper C)
set(CMAKE_C_STANDARD 11)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(src ${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

file(GLOB LibSourceFiles src/*.c)
add_library(GfxHelper SHARED ${LibSourceFiles})
target_link_libraries(GfxHelper PUBLIC ${GTK3_LIBRARIES})
target_include_directories(GfxHelper PUBLIC ${GTK3_INCLUDE_DIRS})
target_compile_options(GfxHelper PUBLIC ${GTK3_CFLAGS_OTHER})

add_executable(GfxHelperDemo examples/main_soleil.c)
add_dependencies(GfxHelperDemo GfxHelper)
target_link_libraries(GfxHelperDemo PUBLIC GfxHelper ${GTK3_LIBRARIES})
target_include_directories(GfxHelperDemo PUBLIC ${GTK3_INCLUDE_DIRS})
target_compile_options(GfxHelperDemo PUBLIC ${GTK3_CFLAGS_OTHER})
