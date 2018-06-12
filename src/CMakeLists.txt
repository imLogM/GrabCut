cmake_minimum_required(VERSION 3.8)
project(grab_cut)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O0")
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wextra -pedantic -Wno-long-long")
endif()
set(CMAKE_CXX_STANDARD 11)

set(OpenCV_DIR /home/logm/opencv-2.4.13.6/build/install/share/OpenCV)   # set opencv dir
FIND_PACKAGE( OpenCV 2 REQUIRED )

set(OpenCV_LIB_DIR /home/logm/opencv-2.4.13.6/build/install/lib)    # set opencv library dir
link_directories ( ${OpenCV_LIB_DIR} )
MESSAGE(STATUS "OpenCV_LIB_DIR: ${OpenCV_LIB_DIR}")
MESSAGE(STATUS "OpenCV_LIBS: ${OpenCV_LIBS}")

include_directories ( ${OpenCV_INCLUDE_DIRS} )      # set opencv include dir
MESSAGE(STATUS "OpenCV_INCLUDE_DIRS: ${OpenCV_INCLUDE_DIRS}")

include_directories(${CMAKE_SOURCE_DIR})

set(SOURCE_FILES opencv_demo.cpp)
add_executable(example ${SOURCE_FILES})
target_link_libraries(example ${OpenCV_LIBS})
