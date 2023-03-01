# CMakeList.txt : CMake project for BasicCmakeSetup, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("NDIReceiver")

# Add source to this project's executable.
add_executable (NDI-console "main.cpp")
target_link_libraries(NDI-console NDIReceiver-lib ${NDI-LIBS})

add_custom_command(TARGET NDI-console POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
		"${NDI-BIN}/${NDI-DLL}"
		"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${NDI-DLL}"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET NDI-console PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
