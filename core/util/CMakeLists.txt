# CMakeList.txt : CMake project for BasicCmakeSetup, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("NDIReceiver")

target_sources(NDIReceiver-lib PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/FrameBuffer.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/FrameBuffer.h" "${CMAKE_CURRENT_SOURCE_DIR}/Thread.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/Thread.h")
target_include_directories(NDIReceiver-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


# TODO: Add tests and install targets if needed.