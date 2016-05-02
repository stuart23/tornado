cmake_minimum_required(VERSION 3.4)
project(tornado)

add_executable(tornado geometry.cxx state.cxx step.cxx main.cxx)

find_package(OpenCASCADE REQUIRED)
message(${OpenCASCADE_LIBRARIES})
target_link_libraries(tornado ${OpenCASCADE_LIBRARIES})
include_directories(${OpenCASCADE_INCLUDE_DIR})

target_compile_features(tornado PRIVATE cxx_range_for)

install(TARGETS tornado RUNTIME DESTINATION bin)
