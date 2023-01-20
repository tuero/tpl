include_directories(../src)

# add_executable(test_name test_name.cpp)
# target_link_libraries(test_name PUBLIC library_name)
# add_test(test_name test_name)

# Ignore submodule tests
configure_file(${CMAKE_SOURCE_DIR}/CTestCustom.cmake ${CMAKE_BINARY_DIR})
