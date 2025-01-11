CMAKE_MINIMUM_REQUIRED(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)

project(ComplexMatrixAnalyzer)
add_executable(CMA source/main.cpp source/procedures.cpp)

add_subdirectory(matrix)
add_subdirectory(complex_numbers)

target_link_libraries(CMA PUBLIC matrix)
target_link_libraries(CMA PUBLIC complex_numbers)

add_executable(CMAMT source/main_multithreaded.cpp source/procedures.cpp source/multithreaded.cpp)

target_link_libraries(CMAMT PUBLIC matrix)
target_link_libraries(CMAMT PUBLIC complex_numbers)