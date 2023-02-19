cmake_minimum_required(VERSION 3.15)
project(evalLib VERSION 0.1 DESCRIPTION "Eval lib")




# Create an executable
add_library(${PROJECT_NAME}
    SHARED
    fracnum.cpp
)








 
# Linking libraries
target_link_libraries(${PROJECT_NAME}
    gmp
    gmpxx
)
 
# Specify includes

target_include_directories(${PROJECT_NAME} PUBLIC . )


 
# Set C++ version
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)
