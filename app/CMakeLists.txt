cmake_minimum_required(VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("GlassSurf")

include_directories("dependencies/")

set(CXX_FILES  
    "src/windows/process_detector.cpp" 
    "src/main.cpp" "src/windows/window_utilities.cpp" "src/windows/background_image.cpp")

set(HEADER_FILES  
    "src/windows/process_detector.h" "src/windows/window_utilities.h" "src/windows/background_image.h")

# Add source to this project's executable.
add_executable (GlassSurf ${CXX_FILES} ${HEADER_FILES})

set_property(TARGET GlassSurf PROPERTY CXX_STANDARD 17)
set_property(TARGET GlassSurf PROPERTY CXX_STANDARD_REQUIRED ON)

# Link OpenCV libraries
target_link_libraries(GlassSurf
    "${CMAKE_SOURCE_DIR}/dependencies/opencv2/opencv_world480.lib"
)

# Set /MT for Release builds
if (MSVC)
    target_compile_options(GlassSurf PRIVATE /MT$<$<CONFIG:Release>:>)
endif()

# TODO: Add tests and install targets if needed.