cmake_minimum_required(VERSION 2.8)
project(WAVE C CXX)

if(MSVC)
  add_definitions(/EHsc)
  add_definitions(/D_CRT_SECURE_NO_WARNINGS)
  add_definitions(/wd4244) # dear MSVC, im fully aware and confident about my type conversions. stop hammering me. kthx :s
endif(MSVC)

# <wave>
include_directories( "./" )

include_directories( "deps/openal/include" )
include_directories( "deps/stb_vorbis" )

add_subdirectory("deps/openal")
add_subdirectory("deps/stb_vorbis")

file(GLOB WAVELIB_SRCS *.cpp *.hpp *.inl)
add_library(wave-static STATIC ${WAVELIB_SRCS})

add_executable(sample              sample.cc)
target_link_libraries(sample       wave-static openal stb_vorbis)

