cmake_minimum_required (VERSION 3.8)

project("si-units" C CXX)
set(CMAKE_CXX_STANDARD 20)
find_package (Threads REQUIRED)

# check and set for ISA options
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-march=avx2" COMPILER_OPT_ARCH_NATIVE_SUPPORTED)
if (COMPILER_OPT_ARCH_NATIVE_SUPPORTED)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=avx2")
else()
  CHECK_CXX_COMPILER_FLAG("/arch:AVX2" COMPILER_OPT_ARCH_AVX_SUPPORTED)
  if(COMPILER_OPT_ARCH_AVX_SUPPORTED)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:AVX2")
  endif()
endif()

include_directories(./include)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable("test_si" test/si.cpp)
target_link_libraries (test_si ${CMAKE_THREAD_LIBS_INIT})
