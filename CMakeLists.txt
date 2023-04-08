cmake_minimum_required(VERSION 3.8)

project(SimpleTrie)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILECOMMANDS ON)
set(CMAKE_BUILD_TYPE "Release")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING
      "Choose the type of build, options are: Debug Release."
      FORCE)
endif(NOT CMAKE_BUILD_TYPE)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib) 

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB MAIN_SRC ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
file(GLOB MAIN_DLL_SRC ${CMAKE_CURRENT_SOURCE_DIR}/trie_dll.cpp)
file(GLOB OTHER_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)


if (CMAKE_BUILD_TYPE MATCHES "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g -Wall -Wno-empty-body -O0")
elseif(CMAKE_BUILD_TYPE MATCHES "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O2")
else()
endif()


add_library(SimpleTrie SHARED ${MAIN_DLL_SRC} ${OTHER_SRC})
add_executable(SimpleTrieEXE ${MAIN_SRC} ${OTHER_SRC})

