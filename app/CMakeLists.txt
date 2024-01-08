cmake_minimum_required(VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()


project ("GlassSurf")

# -| VCPKG Packages |-----------------------------------

set (VCPKG_INSTALLED_DIR "tools/vcpkg/installed")

set(CMAKE_PREFIX_PATH ${VCPKG_INSTALLED_DIR}/x64-windows)

set(OpenCV_DIR "${VCPKG_INSTALLED_DIR}/x64-windows/share/opencv4")
find_package(OpenCV REQUIRED)

set(WINREG_INCLUDE_PATH "${CMAKE_PREFIX_PATH}/include/winreg")

# -| END VCPKG Packages |-------------------------------

include_directories(${WINREG_INCLUDE_PATH})



set(CXX_FILES  
    "src/windows/process_detector.cpp" 
    "src/main.cpp" "src/windows/window_utilities.cpp" "src/windows/background_image.cpp" "src/image_utilities.cpp")

set(HEADER_FILES  
    "src/windows/process_detector.h" "src/windows/window_utilities.h" "src/windows/background_image.h" "src/image_utilities.h")

# Add source to this project's executable.
add_executable (GlassSurf ${CXX_FILES} ${HEADER_FILES} )

set_property(TARGET GlassSurf PROPERTY CXX_STANDARD 17)
set_property(TARGET GlassSurf PROPERTY CXX_STANDARD_REQUIRED ON)

# Include directories
target_include_directories(GlassSurf PRIVATE ${OpenCV_INCLUDE_DIRS})

# Link libraries
target_link_libraries(GlassSurf PRIVATE ${OpenCV_LIBS})
# TODO: Add tests and install targets if needed.

# -| Copy DLLs |----------------------------------------

set(DLL_FILE_PATTERN "*.dll")


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(DLL_DIR "${CMAKE_PREFIX_PATH}/debug/bin")
else()
    set(DLL_DIR "${CMAKE_PREFIX_PATH}/bin")
endif()

file(GLOB DLLS_TO_COPY "${DLL_DIR}/${DLL_FILE_PATTERN}")

foreach(FILE ${DLLS_TO_COPY})
    file(COPY "${FILE}" DESTINATION "${CMAKE_BINARY_DIR}")
endforeach()


# -| END Copy DLLs |------------------------------------