cmake_minimum_required(VERSION 3.5)
project(GfxHelper C)
set(CMAKE_C_STANDARD 11)
set(APPLE_OPTIONS)
set(DEMOS soleil cymn sapin)

set(PRODUCT_VERSION_MAJOR 1)
set(PRODUCT_VERSION_MINOR 4)
set(PRODUCT_VERSION_PATCH 3)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(src ${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

file(GLOB LibSourceFiles src/*.c)
if(APPLE)
    set(LibSourceFiles ${LibSourceFiles} src/foreground.m)
    set(APPLE_OPTIONS "-framework Foundation" "-framework AppKit" objc)
endif (APPLE)

add_library(GfxHelper SHARED ${LibSourceFiles})
target_link_libraries(GfxHelper PUBLIC ${GTK3_LIBRARIES} ${APPLE_OPTIONS})
target_include_directories(GfxHelper PUBLIC ${GTK3_INCLUDE_DIRS})
target_compile_options(GfxHelper PUBLIC ${GTK3_CFLAGS_OTHER})

# demo projects
foreach(demoProjectName ${DEMOS})
    add_executable(${demoProjectName} examples/main_${demoProjectName}.c)
    add_dependencies(${demoProjectName} GfxHelper)
    target_link_libraries(${demoProjectName} PUBLIC GfxHelper ${GTK3_LIBRARIES} m)
    target_include_directories(${demoProjectName} PUBLIC ${GTK3_INCLUDE_DIRS})
    target_compile_options(${demoProjectName} PUBLIC ${GTK3_CFLAGS_OTHER})
endforeach(demoProjectName)

add_custom_target(examples)
add_dependencies(examples soleil cymn sapin)

set(DEST_DIR "${CMAKE_INSTALL_PREFIX}")
CONFIGURE_FILE("pkg-config.in" "gfxhelper.pc" @ONLY)

install(TARGETS GfxHelper DESTINATION lib/)
install(FILES src/public_header.h DESTINATION include RENAME GfxHelper.h)
install(FILES gfxhelper.pc DESTINATION lib/pkgconfig)
