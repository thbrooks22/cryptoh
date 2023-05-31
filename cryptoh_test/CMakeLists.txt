project(cryptoh_test)
add_subdirectory(.lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Google_Tests_run hash/sha/sha256_test.cpp util/math/gf28_test.cpp)
target_link_libraries(Google_Tests_run cryptoh_lib)
target_link_libraries(Google_Tests_run gtest gtest_main)