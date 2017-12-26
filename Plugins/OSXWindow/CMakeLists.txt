# At least we have cmake 3.

cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project( OSXWindowProject LANGUAGES CXX )

# Enables C++ 11 Flags.

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11")

# Plugin directories.

set( OSXHeaders "${ATL_PLUGIN_DIR}/OSXWindow/include" )
set( OSXSources "${ATL_PLUGIN_DIR}/OSXWindow/src" )

include_directories( PUBLIC "${ATL_INCS}" )
include_directories( PUBLIC "${ATL_EXTERNALS}" )
include_directories( PUBLIC "${OSXHeaders}" )
include_directories( PUBLIC "$<INSTALL_INTERFACE:include>" )
include_directories( PRIVATE "${OSXSources}" )

# Sources files and target definition.

file( GLOB headers "${OSXHeaders}/OSXWindow/*.hpp" "${OSXHeaders}/OSXWindow/*.h" )
file( GLOB sources "${OSXSources}/*.cpp" "${OSXSources}/*.m" "${OSXSources}/*.mm" )

add_library( OSXWindow SHARED ${headers} ${sources} )
target_link_libraries( OSXWindow atl )

# Adds OpenGl library.

include_directories("/System/Library/Frameworks")

find_library(OpenGL_LIBRARY OpenGL)
mark_as_advanced(OpenGL_LIBRARY)
target_link_libraries( OSXWindow ${OpenGL_LIBRARY} )

find_library( COCOA_LIBRARY Cocoa )
target_link_libraries( OSXWindow ${COCOA_LIBRARY} )

find_library(CARBON_LIBRARY Carbon)
mark_as_advanced(CARBON_LIBRARY)
target_link_libraries( OSXWindow ${CARBON_LIBRARY} )

set_target_properties( OSXWindow
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${ATL_LIB_DIR}
	    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${ATL_LIB_DIR}
	    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${ATL_LIB_DIR}
        LIBRARY_OUTPUT_DIRECTORY ${ATL_LIB_DIR}
	    LIBRARY_OUTPUT_DIRECTORY_DEBUG ${ATL_LIB_DIR}
	    LIBRARY_OUTPUT_DIRECTORY_RELEASE ${ATL_LIB_DIR}
        RUNTIME_OUTPUT_DIRECTORY ${ATL_LIB_DIR}
	    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${ATL_LIB_DIR}
	    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${ATL_LIB_DIR}
)

# Try to set C++11 Flags for Xcode Projects.

if(${CMAKE_GENERATOR} MATCHES "Xcode")

    macro (set_xcode_property TARGET XCODE_PROPERTY XCODE_VALUE)
        set_property (TARGET ${TARGET} PROPERTY XCODE_ATTRIBUTE_${XCODE_PROPERTY}
                      ${XCODE_VALUE})
    endmacro (set_xcode_property)

    set_xcode_property(OSXWindow CLANG_CXX_LANGUAGE_STANDARD "c++11")
    set_xcode_property(OSXWindow CLANG_CXX_LIBRARY "libc++")

    set_property(TARGET OSXWindow PROPERTY CXX_STANDARD 11)
    set_property(TARGET OSXWindow PROPERTY CXX_STANDARD_REQUIRED ON)

else()

    set_property(TARGET OSXWindow PROPERTY CXX_STANDARD 11)
    set_property(TARGET OSXWindow PROPERTY CXX_STANDARD_REQUIRED ON)

endif(${CMAKE_GENERATOR} MATCHES "Xcode")
