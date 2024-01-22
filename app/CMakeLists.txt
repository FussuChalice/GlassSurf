cmake_minimum_required(VERSION 3.15)

project(GlassSurf CXX)

set (CXX_FILES "src/main.cpp" "src/image_utilities.cpp" 
"src/windows/background_image.cpp" "src/windows/process_detector.cpp" 
"src/windows/window_utilities.cpp" "src/settings/settings_manager.cpp" "src/arguments.cpp")

set (HEADER_FILES "src/image_utilities.h" 
"src/windows/background_image.h" "src/windows/process_detector.h" "src/windows/window_utilities.h" "src/settings/settings_manager.h" "src/arguments.h" "src/base64.hpp")

add_executable(GlassSurf ${CXX_FILES} ${HEADER_FILES})

find_package(argparse)
find_package(OpenCV)
find_package(fltk)
find_package(nlohmann_json)
find_package(beauty)
target_link_libraries(GlassSurf argparse::argparse opencv::opencv fltk::fltk nlohmann_json::nlohmann_json beauty::beauty)

include_directories("./deps/include/")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)