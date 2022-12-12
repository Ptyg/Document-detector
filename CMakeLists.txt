cmake_minimum_required (VERSION 3.8)

set( CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY" )
set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTOUIC ON )

project ( 
	Document_detector
	VERSION 1.0.0
)

add_subdirectory ("Document_detector")