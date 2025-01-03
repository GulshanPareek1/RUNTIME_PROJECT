# # Operators/CMakeLists.txt
# add_library(Operators
#     src/Conv2d.cpp
#     src/Relu.cpp
#     src/MaxPool2d.cpp
#     include/Conv2d.h
#     include/Relu.h
#     include/MaxPool2d.h
# )

# target_include_directories(Operators PUBLIC include)

# # Link against Utilities if Operators depend on it
# target_link_libraries(Operators PUBLIC Utilities)

add_library(Operators
    src/Conv2DLayer.cpp
    include/Conv2DLayer.h
)

target_include_directories(Operators PUBLIC include)