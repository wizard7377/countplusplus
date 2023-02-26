cmake_minimum_required(VERSION 3.15)
project(evalLib VERSION 0.1 DESCRIPTION "Eval lib")


find_package(BISON)
find_package(FLEX)

BISON_TARGET(MyParser parser.yy ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp)
FLEX_TARGET(MyScanner lexer.lex  ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)
ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)

include_directories(${CMAKE_CURRENT_BINARY_DIR})


# Create an executable
add_library(${PROJECT_NAME}
    SHARED
    driver.cc
    fracnum.cpp
    eval.cpp
    ${BISON_MyParser_OUTPUTS}
    ${FLEX_MyScanner_OUTPUTS}
)








 
# Linking libraries
target_link_libraries(${PROJECT_NAME}
    gmp
    gmpxx
    ${FLEX_LIBRARIES}
)
 
# Specify includes

target_include_directories(${PROJECT_NAME} PUBLIC . )


 
# Set C++ version
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)
