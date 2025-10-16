cmake_minimum_required(VERSION 3.14)
project(bolbol-engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG        3.3.10
)

FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG        v0.1.36
)

FetchContent_MakeAvailable(glfw glad)

# Build a small static glad library from the fetched source
add_library(glad_lib STATIC ${glad_SOURCE_DIR}/src/glad.c)
target_include_directories(glad_lib PUBLIC ${glad_SOURCE_DIR}/include)

add_subdirectory(opengl)

add_executable(bolbol main.cpp)
target_include_directories(bolbol PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/opengl)
target_link_libraries(bolbol PRIVATE engine_opengl glfw glad_lib)

if(WIN32)
  target_link_libraries(bolbol PRIVATE opengl32)
endif()
