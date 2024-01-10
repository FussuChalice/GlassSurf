cmake_minimum_required(VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()


project ("GlassSurf")

function(CopyFiles SRC_DIR DST_DIR PATTERN)
    file(GLOB files "${SRC_DIR}/${PATTERN}")
    foreach(file ${files})
        get_filename_component(file_name ${file} NAME)
        configure_file(${file} ${DST_DIR}/${file_name} COPYONLY)
    endforeach()
endfunction()

set(CXX_FILES  
    "src/windows/process_detector.cpp" 
    "src/main.cpp" "src/windows/window_utilities.cpp" "src/windows/background_image.cpp" "src/image_utilities.cpp")

set(HEADER_FILES  
    "src/windows/process_detector.h" "src/windows/window_utilities.h" "src/windows/background_image.h" "src/image_utilities.h")

# Add source to this project's executable.
add_executable (GlassSurf ${CXX_FILES} ${HEADER_FILES})

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(DEPS_PATH "${CMAKE_SOURCE_DIR}/deps/debug/")
endif()
    
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(DEPS_PATH "${CMAKE_SOURCE_DIR}/deps/release/")
endif()

target_link_libraries(GlassSurf
    "${DEPS_PATH}lib/opencv_world480.lib"
)

include_directories("${DEPS_PATH}include/")

CopyFiles("${DEPS_PATH}/dll/" "${CMAKE_BINARY_DIR}" "*.dll")

set_property(TARGET GlassSurf PROPERTY CXX_STANDARD 17)
set_property(TARGET GlassSurf PROPERTY CXX_STANDARD_REQUIRED ON)