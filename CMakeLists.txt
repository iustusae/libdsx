cmake_minimum_required(VERSION 3.10)
project(libdsx VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Create the library target
add_library(libdsx STATIC
    src/vector.cpp
)

# Set the include directories for the library target
target_include_directories(libdsx
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Set the target name of the library (libdsx)
set_target_properties(libdsx PROPERTIES
    OUTPUT_NAME "dsx"
)

# Install the library and headers
install(TARGETS libdsx
    EXPORT libdsxTargets
    ARCHIVE DESTINATION lib
)
install(DIRECTORY include/libdsx
    DESTINATION include
)

# Optionally, you can export the target to be used by other CMake projects
export(TARGETS libdsx
    NAMESPACE libdsx::
    FILE "${CMAKE_CURRENT_BINARY_DIR}/libdsxTargets.cmake"
)
