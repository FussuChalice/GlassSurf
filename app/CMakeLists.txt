# CMakeList.txt : CMake project for CHROME_VIBRANCY, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("BROWSER_VIBRANCY")

# Set the path to the OpenCV directory (change this to the actual path on your system)
set(OpenCV_DIR "lib/opencv2") # Change this to the correct path

# Include OpenCV header files
include_directories("${OpenCV_DIR}/include")

set(CXX_FILES  
	"src/windows/process_detector.cpp" 
	"src/main.cpp" "src/windows/image_utilities.cpp")

set(HEADER_FILES  
	"src/windows/process_detector.h" "src/windows/image_utilities.h" 
	"src/windows/pch.h" )

# Add source to this project's executable.
add_executable (BROWSER_VIBRANCY ${CXX_FILES} ${HEADER_FILES})

set_property(TARGET BROWSER_VIBRANCY PROPERTY CXX_STANDARD 17)
set_property(TARGET BROWSER_VIBRANCY PROPERTY CXX_STANDARD_REQUIRED ON)

# Link OpenCV libraries
target_link_libraries(BROWSER_VIBRANCY 
    "${OpenCV_DIR}/lib/opencv_world480.lib"
)

# TODO: Add tests and install targets if needed.