cmake_minimum_required(VERSION 2.8)
get_filename_component(PROJECT_LOCATION ${CMAKE_SOURCE_DIR} NAME)

#################################
########### EDIT HERE ###########

### Project information ###
set(VER_MAJOR "0")
set(VER_MINOR "0")
set(VER_PATCH "0")
project(PROJECT_LOCATION)

### Add or remove packages ###
set(CMAKE_CXX_FLAGS "-g -Wall -lglut -lGLU -lGL")
set(CMAKE_CXX_FLAGS "-std=c++11")

### Set the gtest location ###
set(GTEST_DIR ext/gmock/gtest)
set(GMOCK_DIR ext/gmock)

### Set the boost location ###
find_package(Boost 1.52 COMPONENTS system filesystem REQUIRED)

set(USE_TESTS true)

########### EDIT HERE ###########
#################################

set(VERSION "${VER_MAJOR}.${VER_MINOR}.${VER_PATCH}")
# So we can build outside of the main directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB files_INC
      "./src/core/*.h"
      "./src/interface/*.h"
)
file(GLOB files_SRC
      "./src/core/*.cpp"
      "./src/interface/*.cpp"
)

####################
## Begin building ##
####################

# Build tests
if(USE_TESTS)

# Include all gtest files
include(${GTEST_DIR}/cmake/internal_utils.cmake)
config_compiler_and_linker()  # Defined in internal_utils.cmake.
include_directories(
  ${GTEST_DIR}/include
  ${GTEST_DIR}
  ${GMOCK_DIR}/include
  ${GMOCK_DIR}
  ${BOOST_INCLUDE_DIR})
link_directories(   ${gtest_BINARY_DIR}/src
                    ${BOOST_LIBRARY_DIRS})

# Tell CMake about the libraries
cxx_library(gtest "${cxx_strict}" ${GTEST_DIR}/src/gtest-all.cc)
cxx_library(gtest_main "${cxx_strict}" ${GTEST_DIR}/src/gtest_main.cc)
cxx_library(gmock "${cxx_strict}" ${GMOCK_DIR}/src/gmock-all.cc)
target_link_libraries(gtest_main gtest gmock)

# Tell CMake about source files
file(GLOB tests_SRC
 "tests/*.cc"
)

#list(LENGTH files_INC number_of_includes)
#if(number_of_includes GREATER 0)
add_executable(unittests ${tests_SRC} ${files_SRC} ${files_INC}) 
target_link_libraries(unittests gtest_main ${Boost_LIBRARIES})
      #   endif()

endif(USE_TESTS)

# Build the real deal
add_executable(main src/main.cpp ${files_SRC})
target_link_libraries(main ${Boost_LIBRARIES})
