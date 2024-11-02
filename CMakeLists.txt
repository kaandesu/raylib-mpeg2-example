cmake_minimum_required(VERSION 3.0)
project(MyProject C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(MPEGS REQUIRED libmpeg2)

include_directories(${MPEGS_INCLUDE_DIRS})
link_directories(${MPEGS_LIBRARY_DIRS})
set(RAYLIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/raylib")
set(MPEG2_INCLUDE_DIR "/opt/homebrew/include")
set(MPEG2_LIB_DIR "/opt/homebrew/lib")

include_directories(${RAYLIB_DIR}/include ${MPEG2_INCLUDE_DIR})

add_executable(my_program src/main.c)

target_link_libraries(my_program ${MPEGS_LIBRARIES} "${RAYLIB_DIR}/libraylib.a")
target_link_libraries(my_program 
    "${RAYLIB_DIR}/libraylib.a" 
    "-lmpeg2convert" 
    "-framework Cocoa" 
    "-framework OpenGL" 
    "-framework IOKit" 
    "-framework CoreVideo" 
    ${REQ_LIBRARIES} 
)

include_directories(${MPEG2_INCLUDE_DIR} ${REQ_INCLUDE_DIRS})

link_directories(${MPEG2_LIB_DIR})
