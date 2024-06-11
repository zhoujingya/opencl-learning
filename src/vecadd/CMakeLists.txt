add_executable(vecadd vecadd.cpp)
target_compile_definitions(vecadd PRIVATE VECADD_SOURCE="${CMAKE_CURRENT_SOURCE_DIR}/vecadd.cl")
