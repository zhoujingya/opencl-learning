cmake_minimum_required(VERSION 3.10)
project(opecl-learning)

# Runtime output directory
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find normal opencl driver
find_package(OpenCL REQUIRED)
message( STATUS " OpenCL_FOUND " ${OpenCL_FOUND})
message( STATUS " OpenCL_Library " ${OpenCL_LIBRARY})
set(OPENCL_LIB ${OpenCL_LIBRARY})
if(ENABLE_CUDA)
  cmake_policy(SET CMP0146 OLD)
  find_package(CUDA REQUIRED)
  set(OPENCL_LIB ${CUDA_OpenCL_LIBRARY})
endif(ENABLE_CUDA)

include_directories(utils SYSTEM)

add_subdirectory(utils)
add_subdirectory(src)
