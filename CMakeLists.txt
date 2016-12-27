cmake_minimum_required(VERSION 3.6)

project(Enity)

set(CMAKE_CXX_STANDARD 11)

set(BUILD_SHARED_LIBS FALSE CACHE BOOL "TRUE to build Enity as shared libraries, FALSE to build it as static libraries" FORCE)

set(SOURCE_LIB
        src/Component.h
        src/Entity.h
        src/System.h
        src/World.h
        src/SystemHandler.h
        src/Utility.h
        src/Entity.cpp
        src/World.cpp
        )

if(${BUILD_SHARED_LIBS})
    add_library(Enity SHARED ${SOURCE_LIB})
else()
    add_library(Enity STATIC ${SOURCE_LIB})
endif()