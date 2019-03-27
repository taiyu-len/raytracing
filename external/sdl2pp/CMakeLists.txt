find_package(SDL2PP REQUIRED)

# create sdl2pp target
add_library(SDL2PP INTERFACE IMPORTED GLOBAL)

# add usage requirements to targets that depend on sdl2pp
target_link_libraries(SDL2PP INTERFACE ${SDL2PP_LIBRARIES})
target_include_directories(SDL2PP INTERFACE ${SDL2PP_INCLUDE_DIRS})
