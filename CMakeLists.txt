cmake_minimum_required (VERSION 2.6)

project(grasp)

set(CMAKE_C_FLAGS "%${CMAKE_C_FLAGS} -Wno-unused-parameter")
set(CMAKE_CXX_FLAGS "%${CMAKE_C_FLAGS} -Wno-unused-parameter -Wall -std=c++14")

include_directories(include)
include_directories(src)

add_library(DEP
  src/graph.cc
  src/grasp.cc
  )

add_executable(grasp-executable 
	src/main.cc
	)

target_include_directories (DEP PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(grasp-executable LINK_PUBLIC DEP)
