cmake_minimum_required(VERSION 3.4)
project(tornado)

add_executable(tornado geometry.cxx state.cxx step.cxx mesh.cxx vtk.cxx main.cxx)

find_package(OpenCASCADE REQUIRED)
target_link_libraries(tornado ${OpenCASCADE_LIBRARIES})
include_directories(${OpenCASCADE_INCLUDE_DIR})

find_package(Armadillo REQUIRED)
target_link_libraries(tornado ${Armadillo_LIBRARIES})
include_directories(${Armadillo_INCLUDE_DIR})

find_package(VTK REQUIRED)
target_link_libraries(tornado ${VTK_LIBRARIES})
include_directories(${VTK_INCLUDE_DIRS})
include(${VTK_USE_FILE})

find_package(Boost REQUIRED) 
include_directories(${Boost_INCLUDE_DIRS}) 
target_link_libraries(tornado ${Boost_LIBRARIES})

target_compile_features(tornado PRIVATE cxx_range_for)

install(TARGETS tornado RUNTIME DESTINATION bin)
