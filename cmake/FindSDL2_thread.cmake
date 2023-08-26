find_path(SDL2_THREAD_INCLUDE_DIR SDL_thread.h)
include_directories(${SDL2_THREAD_INCLUDE_DIR})

# PREFER STATIC LIBRARIES ########
# cmake respects the order of extensions when looking for libraries
SET(CMAKE_FIND_LIBRARY_SUFFIXES .lib .a ${CMAKE_FIND_LIBRARY_SUFFIXES})
# ------------------- ########

find_library(SDL2_THREAD_LIBRARY NAMES SDL2_thread PATH_SUFFIXES lib ${VC_LIB_PATH_SUFFIX})
set(SDL2_THREAD ${SDL2_THREAD_LIBRARY})

