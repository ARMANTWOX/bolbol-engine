add_library(engine_opengl
  Renderer.cpp
  Shader.cpp
)

target_include_directories(engine_opengl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(engine_opengl PRIVATE glfw glad_lib)

# If glm was provided via FetchContent, make sure headers are visible
if(TARGET glm)
  target_include_directories(engine_opengl PUBLIC ${glm_SOURCE_DIR})
endif()
