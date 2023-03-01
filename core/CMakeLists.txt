# CMakeList.txt : CMake project for BasicCmakeSetup, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("NDIReceiver")

# Add source to this project's executable.
add_library (NDIReceiver-lib STATIC "Thread.h" "Thread.cpp" "Receiver.cpp" "Receiver.h")
target_include_directories(NDIReceiver-lib PUBLIC "${CMAKE_SOURCE_DIR}/core" "${NDI-INCLUDES}")


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET NDIReceiver-lib PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
