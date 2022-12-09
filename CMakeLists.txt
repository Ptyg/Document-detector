cmake_minimum_required (VERSION 3.8)

set( CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY" )
set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTOUIC ON )

if( CMAKE_CONFIGURATION_TYPES )
    message( "Multi-configuration generator: " ${CMAKE_CONFIGURATION_TYPES} )
else()
    message( "Single-configuration generator " )
	
	if( CMAKE_BUILD_TYPE MATCHES Debug )
		set( VCPKG_BUILD_TYPE debug )
	else()
		set( VCPKG_BUILD_TYPE release )
	endif()
	
	message("Mode: " ${VCPKG_BUILD_TYPE})
endif()

message("Target triplet for debug is " ${VCPKG_TARGET_TRIPLET})


project ( 
	Document_detector
	VERSION 1.0.0
)

add_subdirectory ("Document_detector")