# ------------------------------------------------------- #
#
# File:   Examples/FirstExample/CMakeLists.txt
# Author: Luk2010
# Date:   24/10/2017
#
# ------------------------------------------------------- #
project(AtlFirstExample VERSION 1 LANGUAGES CXX)

# Sources files.

AtlMakeExecutable( firstexample main.cpp )
target_link_libraries( firstexample atl )

# Headers files.
include_directories(PUBLIC
        ${ATL_INCS}
        ${ATL_EXTERNALS}
        $<INSTALL_INTERFACE:include>
        PRIVATE src)

set_target_properties( firstexample
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

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11")