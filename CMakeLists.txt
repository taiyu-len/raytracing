cmake_minimum_required(VERSION 3.11)
project(ray_tracer VERSION 0.1)

# add ./cmake to module path
list(INSERT CMAKE_MODULE_PATH 0 "${RayTracer_SOURCE_DIR}/cmake")

# add external targets
add_subdirectory(external)

# define ray_tracer target
add_executable(ray_tracer)

target_sources(ray_tracer PRIVATE
	"src/main.cpp"
	"src/rng.cpp"
	"src/window.cpp"
	"src/render.cpp"
	"src/camera.cpp"
	"src/color.cpp"
	"src/world.cpp"
	"src/sphere.cpp"
	"src/plane.cpp"
	"src/material.cpp"
)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address")
target_compile_options(ray_tracer
	PRIVATE
	"$<$<CONFIG:DEBUG>:-fsanitize=address>"
	"$<$<CONFIG:RELEASE>:-O3>"
)


set_target_properties(ray_tracer PROPERTIES CXX_STANDARD 17)
target_link_libraries(ray_tracer PRIVATE SDL2PP)
target_link_libraries(ray_tracer PRIVATE Threads::Threads)

