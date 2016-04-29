cmake_minimum_required(VERSION 2.6)
project(tornado)

add_executable(tornado geometry.cxx state.cxx step.cxx main.cxx)

install(TARGETS tornado RUNTIME DESTINATION bin)
