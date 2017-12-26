# =========================================================================
#
# File: Gl3Driver/CMakeLists.txt
# Author: Luk2010
# Date: 15/10/2017
#
# Purpose: Creates the generic OpenGL3 driver for ATL engine.
#
# =========================================================================
project( Gl3Driver LANGUAGES CXX )
set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11" )

# Plugin directories
set( Gl3DriverHeadersDir "${ATL_PLUGIN_DIR}/Gl3Driver/include" )
set( Gl3DriverSourcesDir "${ATL_PLUGIN_DIR}/Gl3Driver/src" )

include_directories( PUBLIC "$<INSTALL_INTERFACE:include>" )
include_directories( PUBLIC "${ATL_INCS}" )
include_directories( PUBLIC "${ATL_EXTERNALS}" )
include_directories( PUBLIC "${Gl3DriverHeadersDir}" )
include_directories( PRIVATE "${Gl3DriverSourcesDir}" )

# Sources files
file( GLOB Gl3DriverHeaders "${Gl3DriverHeadersDir}/Gl3Driver/*.h" )
file( GLOB Gl3DriverSources "${Gl3DriverSourcesDir}/*.cpp" "${Gl3DriverSourcesDir}/*.m" "${Gl3DriverSourcesDir}/*.mm" )

add_library( Gl3Driver SHARED ${Gl3DriverHeaders} ${Gl3DriverSources} )
target_link_libraries( Gl3Driver atl )

# Adds OpenGL on macOS platforms.
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

include_directories("/System/Library/Frameworks")

find_library(OpenGL_LIBRARY OpenGL)
mark_as_advanced(OpenGL_LIBRARY)
target_link_libraries( Gl3Driver ${OpenGL_LIBRARY} )

find_library( COCOA_LIBRARY Cocoa )
target_link_libraries( Gl3Driver ${COCOA_LIBRARY} )

file( GLOB Gl3DriverOSXI "${Gl3DriverHeadersDir}/Gl3Driver/OSX/*.h" )
file( GLOB Gl3DriverOSXS "${Gl3DriverSourcesDir}/OSX/*.mm" "${Gl3DriverSourcesDir}/OSX/*.cpp" "${Gl3DriverSourcesDir}/OSX/*.m" )
target_sources( Gl3Driver PRIVATE ${Gl3DriverOSXI} ${Gl3DriverOSXS} )

endif()

set_target_properties( Gl3Driver
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY            ${ATL_LIB_DIR}
	    ARCHIVE_OUTPUT_DIRECTORY_DEBUG      ${ATL_LIB_DIR}
	    ARCHIVE_OUTPUT_DIRECTORY_RELEASE    ${ATL_LIB_DIR}
        LIBRARY_OUTPUT_DIRECTORY            ${ATL_LIB_DIR}
	    LIBRARY_OUTPUT_DIRECTORY_DEBUG      ${ATL_LIB_DIR}
	    LIBRARY_OUTPUT_DIRECTORY_RELEASE    ${ATL_LIB_DIR}
        RUNTIME_OUTPUT_DIRECTORY            ${ATL_LIB_DIR}
	    RUNTIME_OUTPUT_DIRECTORY_DEBUG      ${ATL_LIB_DIR}
	    RUNTIME_OUTPUT_DIRECTORY_RELEASE    ${ATL_LIB_DIR}
)

# Try to set C++11 Flags for Xcode Projects.

if(${CMAKE_GENERATOR} MATCHES "Xcode")

    macro (set_xcode_property TARGET XCODE_PROPERTY XCODE_VALUE)
        set_property (TARGET ${TARGET} PROPERTY XCODE_ATTRIBUTE_${XCODE_PROPERTY}
                      ${XCODE_VALUE})
    endmacro (set_xcode_property)

    set_xcode_property(Gl3Driver CLANG_CXX_LANGUAGE_STANDARD "c++11")
    set_xcode_property(Gl3Driver CLANG_CXX_LIBRARY "libc++")

    set_property(TARGET Gl3Driver PROPERTY CXX_STANDARD 11)
    set_property(TARGET Gl3Driver PROPERTY CXX_STANDARD_REQUIRED ON)

else()

    set_property(TARGET Gl3Driver PROPERTY CXX_STANDARD 11)
    set_property(TARGET Gl3Driver PROPERTY CXX_STANDARD_REQUIRED ON)

endif(${CMAKE_GENERATOR} MATCHES "Xcode")
