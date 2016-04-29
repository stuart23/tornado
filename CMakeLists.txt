cmake_minimum_required(VERSION 3.5)
MESSAGE( STATUS "CMAKE_BINARY_DIR: " ${CMAKE_BINARY_DIR} )
MESSAGE( STATUS "CMAKE_COMMAND: " ${CMAKE_COMMAND} )
project(tornado)

#add_executable(tornado geometry.cxx state.cxx step.cxx main.cxx)
add_executable(tornado main.cxx)

find_package(OpenCASCADE REQUIRED)
message(${OpenCASCADE_INCLUDE_DIR})
message(${OpenCASCADE_LIBRARIES})
include_directories(${OpenCASCADE_INCLUDE_DIR})
target_link_libraries(tornado ${OpenCASCADE_LIBRARIES})

target_compile_features(tornado PRIVATE cxx_range_for)

install(TARGETS tornado RUNTIME DESTINATION bin)
