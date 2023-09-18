cmake_minimum_required(VERSION 3.10)

project(balboa)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_BUILD_TYPE RelWithDebInfo)

if(MSVC)
  add_compile_options(/Wall)
else()
  add_compile_options(-Wall)
endif()

include_directories(${CMAKE_SOURCE_DIR}/src)

set(SRCS src/3rdparty/json.hpp
         src/3rdparty/stb_image.h
         src/3rdparty/stb_image_write.h
         src/flexception.h
         src/hw1.h
         src/hw1_scenes.h
         src/hw2.h
         src/hw2_scenes.h
         src/image.h
         src/matrix.h
         src/timer.h
         src/vector.h
         src/hw1.cpp
         src/hw1_scenes.cpp
         src/hw2.cpp
         src/hw2_scenes.cpp
         src/image.cpp)

add_library(balboa_lib STATIC ${SRCS})
add_executable(balboa src/main.cpp)

target_link_libraries(balboa balboa_lib)
