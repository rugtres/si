cmake_minimum_required (VERSION 3.8)

project("si-units" C CXX)
set(CMAKE_CXX_STANDARD 20)

include_directories(./include)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable("si" test/si.cpp)
# move to a common destination
install(TARGETS si RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/test)
