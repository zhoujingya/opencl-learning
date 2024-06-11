cmake_minimum_required(VERSION 3.13.4)
project(opecl-learning)

# Runtime output directory
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# find_package(OpenCL REQUIRED)
find_package(CUDA REQUIRED)
message(" CUDA_FOUND" STATUS ${CUDA_OpenCL_LIBRARY})

include_directories(utils SYSTEM)

add_subdirectory(utils)
add_subdirectory(src)
