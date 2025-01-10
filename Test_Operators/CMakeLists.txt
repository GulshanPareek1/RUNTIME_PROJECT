

# Add tests for ConvolutionLayer
add_executable(Test_ConvolutionLayer src/Test_ConvolutionLayer.cpp)
target_include_directories(Test_ConvolutionLayer PRIVATE ../include)
target_link_libraries(Test_ConvolutionLayer PRIVATE Operators)

# Add tests for MaxPoolingLayer
add_executable(Test_MaxPoolingLayer src/Test_MaxPoolingLayer.cpp)
target_include_directories(Test_MaxPoolingLayer PRIVATE ../include)
target_link_libraries(Test_MaxPoolingLayer PRIVATE Operators)

add_executable(Test_LinearLayer src/Test_LinearLayer.cpp)
target_include_directories(Test_LinearLayer PRIVATE ../include)
target_link_libraries(Test_LinearLayer PRIVATE Operators)

add_executable(Test_ReluLayer src/Test_ReluLayer.cpp)
target_include_directories(Test_ReluLayer PRIVATE ../include)
target_link_libraries(Test_ReluLayer PRIVATE Operators)

add_executable(Test_FlattenLayer src/Test_FlattenLayer.cpp)
target_include_directories(Test_FlattenLayer PRIVATE ../include)
target_link_libraries(Test_FlattenLayer PRIVATE Operators)