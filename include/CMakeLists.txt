# CMakeLists.txt for cnpy

# Create a library for cnpy
add_library(cnpy STATIC
    include/cnpy/cnpy.h       # Header file (inside the nested include folder)
    src/cnpy/cnpy.cpp         # Source file (inside the nested src folder)
)

# Include the headers for this library
target_include_directories(cnpy PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include # Include folder for cnpy headers
)
# Link zlib to the cnpy library
# find_package(ZLIB REQUIRED)
# target_link_libraries(cnpy PUBLIC Utilities)

find_package(ZLIB REQUIRED)

include_directories(${ZLIB_INCLUDE_DIRS})

# add_library(cnpy SHARED "cnpy.cpp")
target_link_libraries(cnpy ${ZLIB_LIBRARIES})