# CMakeList.txt : CMake project for CHROME_VIBRANCY, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("GlassSurf")

include_directories("lib/")

set(CXX_FILES  
	"src/windows/process_detector.cpp" 
	"src/main.cpp" "src/image_utilities.cpp" "src/server/controller.cpp" "src/server/server.cpp" "src/settings.cpp")

set(HEADER_FILES  
	"src/windows/process_detector.h" "src/image_utilities.h" 
	"src/pch.h" "src/server/controller.h" "src/server/server.h" "src/settings.h")

# Add source to this project's executable.
add_executable (GlassSurf ${CXX_FILES} ${HEADER_FILES})

set_property(TARGET GlassSurf PROPERTY CXX_STANDARD 17)
set_property(TARGET GlassSurf PROPERTY CXX_STANDARD_REQUIRED ON)

# Link OpenCV libraries
target_link_libraries(GlassSurf
    "lib/opencv_world480.lib"
)

# TODO: Add tests and install targets if needed.