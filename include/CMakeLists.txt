# CMakeLists.txt for cnpy
# CMake file for the include directory
cmake_minimum_required(VERSION 3.10)
# Create a library for cnpy
add_library(Include INTERFACE
    # include/cnpy/cnpy.h       # Header file (inside the nested include folder)
    # src/cnpy/cnpy.cpp         # Source file (inside the nested src folder)
)

# Add the path for the header files
target_include_directories(Include INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include1)