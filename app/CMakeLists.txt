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

set (DEPS_DIR "${CMAKE_SOURCE_DIR}/deps/")

target_link_libraries(GlassSurf "${DEPS_DIR}lib/atk-1.0.lib" "${DEPS_DIR}lib/brotlicommon.lib" "${DEPS_DIR}lib/brotlidec.lib" "${DEPS_DIR}lib/brotlienc.lib" "${DEPS_DIR}lib/bz2.lib" "${DEPS_DIR}lib/cairo-gobject.lib" "${DEPS_DIR}lib/cairo-script-interpreter.lib" "${DEPS_DIR}lib/cairo.lib" "${DEPS_DIR}lib/charset.lib" "${DEPS_DIR}lib/epoxy.lib" "${DEPS_DIR}lib/ffi.lib" "${DEPS_DIR}lib/flatbuffers.lib" "${DEPS_DIR}lib/fontconfig.lib" "${DEPS_DIR}lib/freetype.lib" "${DEPS_DIR}lib/fribidi.lib" "${DEPS_DIR}lib/gdk_pixbuf-2.0.lib" "${DEPS_DIR}lib/getopt.lib" "${DEPS_DIR}lib/gio-2.0.lib" "${DEPS_DIR}lib/glib-2.0.lib" "${DEPS_DIR}lib/gmodule-2.0.lib" "${DEPS_DIR}lib/gobject-2.0.lib" "${DEPS_DIR}lib/graphene-1.0.lib" "${DEPS_DIR}lib/gthread-2.0.lib" "${DEPS_DIR}lib/gtk-4.lib" "${DEPS_DIR}lib/harfbuzz-gobject.lib" "${DEPS_DIR}lib/harfbuzz-subset.lib" "${DEPS_DIR}lib/harfbuzz.lib" "${DEPS_DIR}lib/iconv.lib" "${DEPS_DIR}lib/intl.lib" "${DEPS_DIR}lib/jpeg.lib" "${DEPS_DIR}lib/libexpat.lib" "${DEPS_DIR}lib/libpng16.lib" "${DEPS_DIR}lib/libprotobuf-lite.lib" "${DEPS_DIR}lib/libprotobuf.lib" "${DEPS_DIR}lib/libprotoc.lib" "${DEPS_DIR}lib/libsharpyuv.lib" "${DEPS_DIR}lib/libwebp.lib" "${DEPS_DIR}lib/libwebpdecoder.lib" "${DEPS_DIR}lib/libwebpdemux.lib" "${DEPS_DIR}lib/libwebpmux.lib" "${DEPS_DIR}lib/lzma.lib" "${DEPS_DIR}lib/lzo2.lib" "${DEPS_DIR}lib/opencv_calib3d4.lib" "${DEPS_DIR}lib/opencv_core4.lib" "${DEPS_DIR}lib/opencv_dnn4.lib" "${DEPS_DIR}lib/opencv_features2d4.lib" "${DEPS_DIR}lib/opencv_flann4.lib" "${DEPS_DIR}lib/opencv_highgui4.lib" "${DEPS_DIR}lib/opencv_imgcodecs4.lib" "${DEPS_DIR}lib/opencv_imgproc4.lib" "${DEPS_DIR}lib/opencv_ml4.lib" "${DEPS_DIR}lib/opencv_objdetect4.lib" "${DEPS_DIR}lib/opencv_photo4.lib" "${DEPS_DIR}lib/opencv_stitching4.lib" "${DEPS_DIR}lib/opencv_video4.lib" "${DEPS_DIR}lib/opencv_videoio4.lib" "${DEPS_DIR}lib/pango-1.0.lib" "${DEPS_DIR}lib/pangocairo-1.0.lib" "${DEPS_DIR}lib/pangoft2-1.0.lib" "${DEPS_DIR}lib/pangowin32-1.0.lib" "${DEPS_DIR}lib/pcre2-16.lib" "${DEPS_DIR}lib/pcre2-32.lib" "${DEPS_DIR}lib/pcre2-8.lib" "${DEPS_DIR}lib/pcre2-posix.lib" "${DEPS_DIR}lib/pixman-1.lib" "${DEPS_DIR}lib/pthreadVC3.lib" "${DEPS_DIR}lib/pthreadVCE3.lib" "${DEPS_DIR}lib/pthreadVSE3.lib" "${DEPS_DIR}lib/quirc.lib" "${DEPS_DIR}lib/sass.lib" "${DEPS_DIR}lib/tiff.lib" "${DEPS_DIR}lib/turbojpeg.lib" "${DEPS_DIR}lib/zlib.lib" )

include_directories("${DEPS_DIR}include/")

CopyFiles("${DEPS_DIR}dll/" "${CMAKE_BINARY_DIR}" "*.dll")

set_property(TARGET GlassSurf PROPERTY CXX_STANDARD 17)
set_property(TARGET GlassSurf PROPERTY CXX_STANDARD_REQUIRED ON)