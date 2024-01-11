cmake_minimum_required(VERSION 3.15)

project(GlassSurf CXX)

set (CXX_FILES "src/main.cpp" "src/image_utilities.cpp" 
"src/windows/background_image.cpp" "src/windows/process_detector.cpp" "src/windows/window_utilities.cpp")

set (HEADER_FILES "src/image_utilities.h" 
"src/windows/background_image.h" "src/windows/process_detector.h" "src/windows/window_utilities.h")

add_executable(GlassSurf ${CXX_FILES} ${HEADER_FILES})

find_package(argparse)
find_package(OpenCV)
find_package(fltk)
target_link_libraries(GlassSurf argparse::argparse opencv::opencv fltk::fltk)

include_directories("./deps/include/")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)