# utilities/CMakeLists.txt
add_library(Utilities 
src/JsonParser.cpp
src/BinaryFileReader.cpp
)

# Add include directory relative to the utilities folder
target_include_directories(Utilities PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link the Include library to use nlohmann/json.hp
target_link_libraries(Utilities PUBLIC Include)
