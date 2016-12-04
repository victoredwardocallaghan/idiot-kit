add_subdirectory(winsys)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(OUTPUT_BIN "dipshit")

add_executable(${OUTPUT_BIN} main.c)
target_link_libraries(${OUTPUT_BIN} ${REQUIRED_EXTERNAL_LIBS} m) # rt dl)
target_link_libraries(${OUTPUT_BIN} winsys_lib)
