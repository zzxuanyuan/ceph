## erasure code plugins

set(erasure_codelibdir ${LIBRARY_OUTPUT_PATH}/erasure-code)

add_subdirectory(jerasure)
add_subdirectory(lrc)

if (WITH_BETTER_YASM_ELF64) # TODO: check for yasm support
  add_subdirectory(isa)
endif (WITH_BETTER_YASM_ELF64)

add_library(erasure_code ErasureCodePlugin.cc)
target_link_libraries(erasure_code dl)
add_dependencies(erasure_code ${CMAKE_SOURCE_DIR}/src/ceph_ver.h)

add_library(erasure_code_objs OBJECT ErasureCode.cc)
