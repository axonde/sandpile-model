cmake_minimum_required(VERSION 3.5.0)

project(
	sandpile-model
	VERSION 0.1
	DESCRIPTION "C++ Year 2024 labwork 3"
	LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)

# add_subdirectory(deque)
add_subdirectory(parser)
add_subdirectory(utility)
add_subdirectory(vector)
add_subdirectory(bin)

# enable_testing()
# add_subdirectory(tests)
