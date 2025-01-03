# utilities/CMakeLists.txt
add_library(Utilities 
    src/activations.cpp
    include/activations.h
    src/ConfigParser.cpp
    include/ConfigParser.h
    src/NpyReader.cpp
    include/NpyReader.h
)

# Add include directory relative to the utilities folder
target_include_directories(Utilities PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link cnpy to Utilities
# target_link_libraries(Utilities PUBLIC cnpy)
