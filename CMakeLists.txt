cmake_minimum_required(VERSION 3.10)
project(Json)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall")
set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES test/Json_Test.cpp)

set(CMAKE_BUILD_TYPE Debvug)

INCLUDE_DIRECTORIES(./thirdpart/catch2 ./include)

## 添加宏定义
# ADD_DEFINITIONS(-D SQLITE_4_BYTE_ALIGNED_MALLOC)
ADD_EXECUTABLE(Json ${SOURCE_FILES})

# LINK_LIBRARIES( sqlite3 gtest)

TARGET_LINK_LIBRARIES(Json)

