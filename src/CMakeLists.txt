
link_libraries(${OPENCL_LIB} util)
file(GLOB SUBDIRS LIST_DIRECTORIES true RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *)

# List all the directory
foreach(SUBDIR ${SUBDIRS})
  if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIR}")
    add_subdirectory("${SUBDIR}")
  endif()
endforeach()
