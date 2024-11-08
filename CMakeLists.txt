cmake_minimum_required(VERSION 3.0)
project(MyProject C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(MPEGS REQUIRED libmpeg2)

set(RAYLIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/raylib")
set(MPEG2_INCLUDE_DIR "/opt/homebrew/include")

include_directories(${RAYLIB_DIR}/include ${MPEG2_INCLUDE_DIR})
link_directories(${MPEGS_LIBRARY_DIRS})

add_executable(my_program src/main.c)

target_link_libraries(my_program 
    "${RAYLIB_DIR}/libraylib.a" 
    ${MPEGS_LIBRARIES}
    "-lmpeg2convert" 
    "-framework Cocoa" 
    "-framework OpenGL" 
    "-framework IOKit" 
    "-framework CoreVideo" 
)
