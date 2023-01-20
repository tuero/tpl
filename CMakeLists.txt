cmake_minimum_required (VERSION 3.12)

# Set flags
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(ABSL_PROPAGATE_CXX_STD ON)


project(template-project)

# find_package(Torch REQUIRED)

# Testing
enable_testing()

# Build abseil and include for linking for all child targets
add_subdirectory(external/abseil-cpp)
link_libraries( 
    absl::base
    absl::flags
    absl::flags_parse
    absl::hash
    absl::strings
    absl::synchronization
    absl::optional
    absl::time
)

# Build spdlog
add_subdirectory(external/spdlog)
link_libraries(spdlog::spdlog)

# Let child targets include from external libraries not needed to be built as libraries
# ...

# Build child targets
# add_subdirectory(src)
# add_subdirectory(tests)
