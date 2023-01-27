# Source files
set(COMMON_SOURCES
    util/default_flags.cpp 
)


add_library(library_name STATIC ${COMMON_SOURCES})
target_compile_options(library_name PRIVATE 
    -Wall -Wextra 
    $<$<CONFIG:RELEASE>:-O3> $<$<CONFIG:RELEASE>:-DNDEBUG>
    $<$<CONFIG:DEBUG>:-g> $<$<CONFIG:DEBUG>:-O0> $<$<CONFIG:DEBUG>:-DDEBUG> $<$<CONFIG:DEBUG>:-pg>
)
target_include_directories(library_name PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(library_name ${TORCH_LIBRARIES})

# Main entry point
add_executable(main main.cpp)
target_link_libraries(main PUBLIC library_name)

target_compile_options(main PUBLIC 
    -Wall -Wextra 
    $<$<CONFIG:RELEASE>:-O3> $<$<CONFIG:RELEASE>:-DNDEBUG>
    $<$<CONFIG:DEBUG>:-g> $<$<CONFIG:DEBUG>:-O0> $<$<CONFIG:DEBUG>:-DDEBUG> $<$<CONFIG:DEBUG>:-pg>
)

include_directories(.)
