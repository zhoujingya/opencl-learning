add_executable(boxadd boxadd.cpp)
target_compile_definitions(boxadd PRIVATE BOXADD_SOURCE="${CMAKE_CURRENT_SOURCE_DIR}/boxadd.cl")
