cmake_minimum_required(VERSION 3.10)

# Set the project name
project(RUNTIME_PROJECT)

# Enable C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the output directories for build files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)#_$(CMAKE_BUILD_TYPE))
set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type" FORCE)


# Include directories for global use
include_directories(
    ${CMAKE_SOURCE_DIR}/include  # Third-party libraries
    ${CMAKE_SOURCE_DIR}/utilities/include  # Add utilities include path
)

# ${CMAKE_SOURCE_DIR}/utilities/include  # Add utilities include path
# Add subdirectories for cnpy, layers, utilities, and tests
add_subdirectory(Include) # Add cnpy as a subdirectory
add_subdirectory(Utilities)
add_subdirectory(Operators)
add_subdirectory(Test_Operators)

add_executable(App src/main.cpp)

# Link libraries to the application
target_link_libraries(App Operators Utilities)
# target_link_libraries(App cnpy Utilities)


