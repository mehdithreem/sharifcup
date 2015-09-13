cmake_minimum_required(VERSION 2.8)
project( phase1 )

find_package( OpenCV )
find_package(Boost 1.40.0 REQUIRED system)
find_package(PythonLibs REQUIRED)


include_directories( ${PYTHON_INCLUDE_DIRS} )
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( ${Boost_INCLUDE_DIRS} )

file(GLOB CONTROLLER_SRC "../Controller/*.cpp")
file(GLOB CORE_SRC "../Core/*.cpp")
file(GLOB PATHFINDING_SRC "../Pathfinding/*.cpp")
file(GLOB UTILITY_SRC "../Utility/*.cpp")
file(GLOB VISION_SRC "../Vision/*.cpp")
file(GLOB PHASE1_SRC "../Phase1/*.cpp")

file(GLOB PHASE1_HDR "../Include/*.h")

set(HEADERS ${PHASE1_HDR})
SET(SOURCE start.cpp Phase1.cpp ${CONTROLLER_SRC} ${CORE_SRC} ${PATHFINDING_SRC} ${UTILITY_SRC} ${VISION_SRC} ${PHASE1_SRC} )

add_executable( phase1 ${SOURCE} ${HEADERS})

target_link_libraries( phase1 ${OpenCV_LIBS} )
target_link_libraries( phase1 ${PYTHON_LIBRARIES})
target_link_libraries( phase1 ${Boost_SYSTEM_LIBRARY})
target_compile_features( phase1 PRIVATE cxx_range_for )