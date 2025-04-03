cmake_minimum_required(VERSION 3.14)
project(CryptoCpp LANGUAGES CXX)

# Set default C++ standard to 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Options to control building of tests & benchmarks
option(BUILD_TESTING "Build unit tests" ON)
option(BUILD_BENCHMARKS "Build benchmarks" ON)

###############################################################################
#                         External Dependencies
###############################################################################

# GoogleTest configuration
set(INSTALL_GTEST OFF)
set(BUILD_GTEST ON)
set(BUILD_GMOCK ON)
set(BUILD_GTEST_TESTS OFF) # Disable GTest's own tests

add_subdirectory(external/gtest)

# Google Benchmark configuration
set(BENCHMARK_ENABLE_TESTING OFF) # Disable Benchmark's own tests
set(BENCHMARK_ENABLE_INSTALL OFF)

add_subdirectory(external/benchmark)

###############################################################################
#                          Library Target
###############################################################################

# Gather all .cpp files inside src/ recursively.
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

# Create a static library from all source files
add_library(cppcrypto STATIC ${SRC_FILES})
target_include_directories(cppcrypto
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# (Optional) Link pthread if needed for concurrency
find_package(Threads REQUIRED)
target_link_libraries(cppcrypto Threads::Threads)

###############################################################################
#                                Unit Tests
###############################################################################
if(BUILD_TESTING)
  enable_testing()

  # Collect all test source files
  file(GLOB_RECURSE TEST_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp"
  )

  # For each test file, create a separate executable and link it to GTest + our library
  foreach(test_file ${TEST_FILES})
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(${test_name} ${test_file})
    target_link_libraries(${test_name}
      PRIVATE
        cppcrypto
        gtest
        gtest_main
    )
    # Register the test with CTest
    add_test(NAME ${test_name} COMMAND ${test_name})
  endforeach()
endif()

###############################################################################
#                                Benchmarks
###############################################################################
if(BUILD_BENCHMARKS)
  file(GLOB_RECURSE BENCH_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/*.cpp"
  )

  # For each benchmark file, create a separate executable and link it to Google Benchmark + our library
  foreach(bench_file ${BENCH_FILES})
    get_filename_component(bench_name ${bench_file} NAME_WE)
    add_executable(${bench_name} ${bench_file})
    target_link_libraries(${bench_name}
      PRIVATE
        cppcrypto
        benchmark::benchmark
        benchmark::benchmark_main
    )
  endforeach()
endif()

###############################################################################
#                      Placeholder for Future Enhancements
###############################################################################
# - Add Doxygen build option and target
# - Install rules for headers and library
# - Separate targets for classical, modern, and post-quantum ciphers
# - Packaging and versioning
