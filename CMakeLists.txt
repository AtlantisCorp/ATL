# At least we have cmake 3.
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(AtlSdk VERSION 1 LANGUAGES CXX)

# Set the GRE_ROOT_DIRECTORY variable.

set(ATL_ROOT_DIR        ${CMAKE_CURRENT_SOURCE_DIR})
set(ATL_INCS           "${ATL_ROOT_DIR}/Main/includes" )
set(ATL_SRCS           "${ATL_ROOT_DIR}/Main/sources" )
set(ATL_LIB_DIR        "${ATL_ROOT_DIR}/libs" )
set(ATL_PLUGIN_DIR     "${ATL_ROOT_DIR}/Plugins" )
set(ATL_EXTERNALS      "${ATL_ROOT_DIR}/Externals" )

# Utilities macros.

# \name  AtlMakeExecutable
# \brief Creates a new executable in the current project using name and sources.
# \desc  Uses this function to add an executable. It will accordingly use executable's 
#        options 'WIN32' or 'MACOSX_BUNDLE' on the correct platform.
macro( AtlMakeExecutable target sources )

if(APPLE)
    add_executable( ${target} MACOSX_BUNDLE ${sources} )
elseif(WIN32)
    add_executable( ${target} WIN32 ${sources} )
else()
    add_executable( ${target} ${sources} )
endif()

endmacro( AtlMakeExecutable )

# Targets we have to make.

add_subdirectory(Main)
add_subdirectory(Plugins)
add_subdirectory(Examples)
