project(libatl VERSION 1.0 LANGUAGES CXX)

# Enables C++ 11 Flags.
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11")

# Sources files.
add_library(atl SHARED "")

file( GLOB ATL_SOURCES_FILES "sources/*.cpp" "includes/ATL/*.hpp" )
target_sources( atl PRIVATE ${ATL_SOURCES_FILES} )

# Headers files.
include_directories(PUBLIC
        ${ATL_INCS}
        "${ATL_ROOT_DIR}/Externals/"
        $<INSTALL_INTERFACE:include>
        PRIVATE src)

# Link with used libraries.
target_link_libraries(atl dl)

# =========================================================================
# Enables only on Linux platform. On Linux , we also links against the libuuid.
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
# =========================================================================

	find_package(PkgConfig REQUIRED)

	pkg_search_module(UUID REQUIRED uuid)
	include_directories(${UUID_INCLUDE_DIRS})
	target_link_libraries(atl ${UUID_LIBRARIES})

	find_package( Threads REQUIRED )
	target_link_libraries(atl ${CMAKE_THREAD_LIBS_INIT})

    # Include Linux specialized files.

    file( GLOB AtlLinuxSources "sources/Linux/*.cpp" "includes/Linux/*.hpp" )
    target_sources( atl PRIVATE ${AtlLinuxSources} )

# =========================================================================
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
# =========================================================================

# =========================================================================
# Enables only on Darwin platform.
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
# =========================================================================

    # Includes macOS Cocoa library.

    include_directories( "/System/Library/Frameworks" )
    find_library( COCOA_LIBRARY Cocoa )
    target_link_libraries( atl ${COCOA_LIBRARY} )

    # Include Darwin specialized files.

    file( GLOB AtlDarwinSources "sources/Darwin/*.cpp" "sources/Darwin/*.mm" "includes/Darwin/*.hpp" )
    target_sources( atl PRIVATE ${AtlDarwinSources} )
    
    # Make the framework. 
    
    set_target_properties( atl PROPERTIES
        FRAMEWORK TRUE 
        FRAMEWORK_VERSION A
        MACOSX_FRAMEWORK_IDENTIFIER com.acorp.atl 
        VERSION 1.0.0 
        SOVERSION 1.0.0
        XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "Mac Developer" 
    )

# =========================================================================
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
# =========================================================================

# =========================================================================
# Enables only on Darwin platform.
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
# =========================================================================

    # Include Darwin specialized files.

    file( GLOB AtlWindowsSources "sources/Windows/*.cpp" "includes/Windows/*.hpp" )
    target_sources( atl PRIVATE ${AtlWindowsSources} )

# =========================================================================
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
# =========================================================================

set_target_properties( atl
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY           ${ATL_LIB_DIR}
	    ARCHIVE_OUTPUT_DIRECTORY_DEBUG     ${ATL_LIB_DIR}
	    ARCHIVE_OUTPUT_DIRECTORY_RELEASE   ${ATL_LIB_DIR}
        LIBRARY_OUTPUT_DIRECTORY           ${ATL_LIB_DIR}
	    LIBRARY_OUTPUT_DIRECTORY_DEBUG     ${ATL_LIB_DIR}
	    LIBRARY_OUTPUT_DIRECTORY_RELEASE   ${ATL_LIB_DIR}
        RUNTIME_OUTPUT_DIRECTORY           ${ATL_LIB_DIR}
	    RUNTIME_OUTPUT_DIRECTORY_DEBUG     ${ATL_LIB_DIR}
	    RUNTIME_OUTPUT_DIRECTORY_RELEASE   ${ATL_LIB_DIR}
)

# Try to set C++11 Flags for Xcode Projects.
if(${CMAKE_GENERATOR} MATCHES "Xcode")

    macro (set_xcode_property TARGET XCODE_PROPERTY XCODE_VALUE)
        set_property (TARGET ${TARGET} PROPERTY XCODE_ATTRIBUTE_${XCODE_PROPERTY}
                      ${XCODE_VALUE})
    endmacro (set_xcode_property)

    set_xcode_property(atl CLANG_CXX_LANGUAGE_STANDARD "c++11")
    set_xcode_property(atl CLANG_CXX_LIBRARY "libc++")

    set_property(TARGET atl PROPERTY CXX_STANDARD 11)
    set_property(TARGET atl PROPERTY CXX_STANDARD_REQUIRED ON)

else()

    set_property(TARGET atl PROPERTY CXX_STANDARD 11)
    set_property(TARGET atl PROPERTY CXX_STANDARD_REQUIRED ON)

endif(${CMAKE_GENERATOR} MATCHES "Xcode")
