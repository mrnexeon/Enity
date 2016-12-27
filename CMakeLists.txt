cmake_minimum_required(VERSION 3.6)

project(Enity)

set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(HEADERS include/Component.h include/Entity.h include/System.h include/SystemHandler.h include/Utility.h include/World.h)
set(SOURCES src/Entity.cpp src/SystemHandler.cpp src/World.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})