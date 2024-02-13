cmake_minimum_required(VERSION 3.14)
project(Gene_Sequencing VERSION 0.1.0 LANGUAGES C CXX)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Include header files
include_directories(include)

# Automatically add all .cpp files in the src directory
file(GLOB SOURCES "src/*.cpp")

# Compile source files into a static library
add_library(gene_sequencing_lib STATIC ${SOURCES})

# Link the library with your main application executable
add_executable(Gene_Sequencing main.cpp)
target_link_libraries(Gene_Sequencing gene_sequencing_lib)

# Set up testing
include(GoogleTest)
add_executable(my_test tests/tests.cc)
target_link_libraries(my_test gtest_main gene_sequencing_lib)
gtest_discover_tests(my_test)
enable_testing()
