cmake_minimum_required(VERSION 3.14)
project(bolbol-engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Try to find system packages first
find_package(glfw3 QUIET)
find_package(glad QUIET)
find_package(glm QUIET)

set(USE_FETCHCONTENT OFF)
if(NOT glfw3_FOUND OR NOT glad_FOUND OR NOT glm_FOUND)
  set(USE_FETCHCONTENT ON)
endif()

# If the user provided local `src/` and `include/` folders (e.g. in third_party or ./src ./include), prefer those
set(LOCAL_THIRD_PARTY_DIR "${CMAKE_SOURCE_DIR}/third_party")
if(EXISTS "${CMAKE_SOURCE_DIR}/src" AND EXISTS "${CMAKE_SOURCE_DIR}/include")
  message(STATUS "Found local src/include; will try to use local libraries before FetchContent")
  set(LOCAL_THIRD_PARTY_DIR "${CMAKE_SOURCE_DIR}")
endif()

# Helper to check for local glad/glfw sources
set(LOCAL_GLAD_C ${LOCAL_THIRD_PARTY_DIR}/glad/src/glad.c)
set(LOCAL_GLAD_INCLUDE ${LOCAL_THIRD_PARTY_DIR}/glad/include)
set(LOCAL_GLFW_DIR ${LOCAL_THIRD_PARTY_DIR}/glfw)

if(EXISTS "${LOCAL_GLAD_C}" AND EXISTS "${LOCAL_GLAD_INCLUDE}")
  message(STATUS "Using local glad at ${LOCAL_GLAD_C}")
  set(USE_LOCAL_GLAD ON)
  set(GLAD_LOCAL_SOURCE ${LOCAL_GLAD_C})
  set(GLAD_LOCAL_INCLUDE ${LOCAL_GLAD_INCLUDE})
endif()

if(EXISTS "${LOCAL_GLFW_DIR}")
  message(STATUS "Using local glfw at ${LOCAL_GLFW_DIR}")
  set(USE_LOCAL_GLFW ON)
  set(GLFW_LOCAL_DIR ${LOCAL_GLFW_DIR})
endif()

if(USE_FETCHCONTENT)
  include(FetchContent)
  if(NOT glfw3_FOUND)
    FetchContent_Declare(
      glfw
      GIT_REPOSITORY https://github.com/glfw/glfw.git
      GIT_TAG        3.3.10
    )
  endif()
  if(NOT glad_FOUND)
    FetchContent_Declare(
      glad
      GIT_REPOSITORY https://github.com/Dav1dde/glad.git
      GIT_TAG        v0.1.36
    )
  endif()
  if(NOT glm_FOUND)
    FetchContent_Declare(
      glm
      GIT_REPOSITORY https://github.com/g-truc/glm.git
      GIT_TAG        0.9.9.8
    )
  endif()
  if(NOT glfw3_FOUND)
    FetchContent_MakeAvailable(glfw)
  endif()
  if(NOT glad_FOUND)
    FetchContent_MakeAvailable(glad)
  endif()
  if(NOT glm_FOUND)
    FetchContent_MakeAvailable(glm)
  endif()
endif()

# glad: use local, system, or build from source (in that order)
if(DEFINED USE_LOCAL_GLAD AND USE_LOCAL_GLAD)
  add_library(glad_lib STATIC ${GLAD_LOCAL_SOURCE})
  target_include_directories(glad_lib PUBLIC ${GLAD_LOCAL_INCLUDE})
  set(GLAD_LIB glad_lib)
  set(GLAD_INCLUDE_DIRS ${GLAD_LOCAL_INCLUDE})
elseif(glad_FOUND)
  set(GLAD_LIB glad)
  set(GLAD_INCLUDE_DIRS ${GLAD_INCLUDE_DIRS})
else()
  add_library(glad_lib STATIC ${glad_SOURCE_DIR}/src/glad.c)
  target_include_directories(glad_lib PUBLIC ${glad_SOURCE_DIR}/include)
  set(GLAD_LIB glad_lib)
  set(GLAD_INCLUDE_DIRS ${glad_SOURCE_DIR}/include)
endif()

add_subdirectory(opengl)

add_executable(bolbol main.cpp)
target_include_directories(bolbol PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/opengl)
target_link_libraries(bolbol PRIVATE engine_opengl)
if(glfw3_FOUND)
  target_link_libraries(bolbol PRIVATE glfw)
else()
  target_link_libraries(bolbol PRIVATE glfw)
endif()
target_link_libraries(bolbol PRIVATE ${GLAD_LIB})

# GLM include for engine_opengl
if(glm_FOUND)
  target_include_directories(engine_opengl PUBLIC ${GLM_INCLUDE_DIRS})
elseif(TARGET glm)
  target_include_directories(engine_opengl PUBLIC ${glm_SOURCE_DIR})
endif()

if(WIN32)
  target_link_libraries(bolbol PRIVATE opengl32)
endif()

if(WIN32)
  target_link_libraries(bolbol PRIVATE opengl32)
endif()
