cmake_minimum_required (VERSION 3.8)

set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTOUIC ON )

# setup libs 
find_package( OpenCV CONFIG REQUIRED )

find_package( Qt5 REQUIRED COMPONENTS
    Core
    Widgets
    Gui
)

# setup sources
set( SOURCES 
    ./src/App.ui
    ./src/App.h
    ./src/App.cpp
    ./src/CvImage.h
    ./src/CvImage.cpp
    ./src/Document_detector.cpp 
)

add_executable ( Document_detector ${SOURCES} )

# link libs
target_link_libraries( Document_detector PRIVATE 
    Qt5::Core
    Qt5::Widgets 
    Qt5::Gui
)
target_link_libraries( Document_detector PRIVATE 
    opencv_core 
    opencv_highgui 
)

set_property( TARGET Document_detector PROPERTY CXX_STANDARD 11 )
