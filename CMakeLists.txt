cmake_minimum_required(VERSION 3.15)
project(countBot VERSION 0.1 DESCRIPTION "A discord bot")

set(FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR /usr/include/mysql)

#Add directories 
include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)
include_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR})
include_directories(secrets;include)
file(GLOB_RECURSE SECRETS "secrets/*.hpp")
file(GLOB_RECURSE INC_SOURCES "include/*.cpp") 
# Add DPP as dependency
add_subdirectory(libs/DPP)
add_subdirectory(eval)
# You can also add any other libs you want to use
#set(CMAKE_CXX_FLAGS "-O0")


add_link_options("-lmysqlclient")


# Create an executable
add_executable(${PROJECT_NAME}
    src/main.cpp
    ${SECRETS}
    ${INC_SOURCES}
)








 
# Linking libraries
target_link_libraries(${PROJECT_NAME}
    dpp
    nlohmann_json::nlohmann_json
    /usr/lib/x86_64-linux-gnu/libmysqlclient.a
    gmp
    gmpxx
    evalLib
)
 
# Specify includes

target_include_directories(${PROJECT_NAME} PUBLIC
    libs/DPP/include
    include/utils
    include/database
    include/eventhandle
    src/commands
)


 
# Set C++ version
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)
