# CMakeList.txt : CMake project for RaceGameV2, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)



project (RaceGameV2)

# Add source to this project's executable.

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable (RaceGameV2 ${SOURCES})


find_package(OpenGL REQUIRED)

find_package(glfw3 CONFIG REQUIRED)


target_link_libraries(RaceGameV2 PRIVATE glfw ${OPENGL_LIBRARY})

# TODO: Add tests and install targets if needed.
