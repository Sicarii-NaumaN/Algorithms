CMAKE_MINIMUM_REQUIRED(VERSION 3.16)
PROJECT(task6)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  ")
set(PROJECT_INCLUDE_DIR project/include/)
include_directories(${PROJECT_INCLUDE_DIR})
set(SRC_FILES ./project/src/main.cpp
        ./project/src/ArcGraph.cpp
        ./project/src/MatrixGraph.cpp
        ./project/src/SetGraph.cpp
        ./project/src/LIstGraph.cpp)
#list(REMOVE_ITEM SRC_FILES ./project/src/main.cpp)

add_library(lib ${SRC_FILES})
ADD_EXECUTABLE(a.out project/src/main.cpp)