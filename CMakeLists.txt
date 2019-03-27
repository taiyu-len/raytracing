cmake_minimum_required(VERSION 3.11)
project(ray_tracer VERSION 0.1)

# add ./cmake to module path
set(CMAKE_MODULE_PATH "${RayTracer_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

# add external targets
add_subdirectory(external)

# define ray_tracer target
add_executable(ray_tracer)
target_sources(ray_tracer PRIVATE
	"src/main.cpp"
	"src/rng.cpp"
	"src/window.cpp"
	"src/camera.cpp"
	"src/color.cpp"
	"src/world.cpp"
	"src/sphere.cpp"
	"src/material.cpp"
)
set_target_properties(ray_tracer PROPERTIES CXX_STANDARD 17)
target_link_libraries(ray_tracer PRIVATE SDL2PP)
