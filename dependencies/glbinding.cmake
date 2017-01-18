set(BUILD_SHARED_LIBS      OFF CACHE BOOL "" FORCE)
set(OPTION_SELF_CONTAINED  OFF CACHE BOOL "" FORCE)
set(OPTION_BUILD_TESTS     OFF CACHE BOOL "" FORCE)
set(OPTION_BUILD_GPU_TESTS OFF CACHE BOOL "" FORCE)
set(OPTION_BUILD_DOCS      OFF CACHE BOOL "" FORCE)
set(OPTION_BUILD_TOOLS     OFF CACHE BOOL "" FORCE)
set(OPTION_BUILD_EXAMPLES  OFF CACHE BOOL "" FORCE)
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/glbinding")