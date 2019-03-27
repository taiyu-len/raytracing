# - Try to find SDL2pp library
#
# Once done this will define
#
#  SDL2PP_FOUND
#  SDL2PP_INCLUDE_DIRS
#  SDL2PP_LIBRARIES

IF(SDL2PP_INCLUDE_DIR AND SDL2PP_LIBRARY)
	# in cache already
	SET(SDL2PP_FIND_QUIETLY TRUE)
ENDIF(SDL2PP_INCLUDE_DIR AND SDL2PP_LIBRARY)

FIND_PATH(SDL2PP_INCLUDE_DIR SDL2pp/SDL2pp.hh HINTS "/usr/include")

FIND_LIBRARY(SDL2PP_LIBRARY NAMES SDL2pp HINTS "/usr/lib")

MARK_AS_ADVANCED(SDL2PP_INCLUDE_DIR SDL2PP_LIBRARY)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDL2PP
	REQUIRED_VARS SDL2PP_INCLUDE_DIR SDL2PP_LIBRARY
)

IF(SDL2PP_FOUND)
	SET(SDL2PP_INCLUDE_DIRS ${SDL2PP_INCLUDE_DIR} "/usr/include/SDL2")
	SET(SDL2PP_LIBRARIES "/usr/lib/libSDL2main.a" ${SDL2PP_LIBRARY} "/usr/lib/libSDL2.so" "/usr/lib/libSDL2_image.so" "/usr/lib/libSDL2_ttf.so" "/usr/lib/libSDL2_mixer.so")
ENDIF(SDL2PP_FOUND)