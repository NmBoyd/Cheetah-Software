# common library (libbiomimetics)

cmake_minimum_required(VERSION 2.8.2)

project(libbiomimetics)

# Source/Include files
include_directories(".")
include_directories("include/" )                 # common includes
include_directories("/usr/local/include/lcm/")   # lcm includes
include_directories("../lcm-types/cpp/")
include_directories("../third-party/inih")       # inih includes
include_directories("../third-party/osqp/include")       # osqp includes
include_directories("../third-party/ParamHandler")
include_directories("/usr/local/include/eigen3")   # lcm includes
include_directories("FootstepPlanner")
include_directories(${CMAKE_BINARY_DIR})
file(GLOB_RECURSE sources "src/*.cpp")                   # common library cpp files

# Library
add_library(biomimetics SHARED ${sources})       # produce a library used by sim/robot
target_link_libraries(biomimetics inih dynacore_param_handler JCQP osqp)

if(CMAKE_SYSTEM_NAME MATCHES Linux)
# Pull in Google Test
include(CTest)
if (CMAKE_VERSION VERSION_LESS 3.2)
    set(UPDATE_DISCONNECTED_IF_AVAILABLE "")
else()
    set(UPDATE_DISCONNECTED_IF_AVAILABLE "UPDATE_DISCONNECTED 1")
endif()
include(DownloadProject.cmake)
download_project(PROJ                googletest
                 GIT_REPOSITORY      https://github.com/google/googletest.git
                 GIT_TAG             master
                 ${UPDATE_DISCONNECTED_IF_AVAILABLE}
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
message(${googletest_SOURCE_DIR})
message(${googletest_BINARY_DIR})
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include"
                        "${gmock_SOURCE_DIR}/include")
endif()

# Test
file(GLOB_RECURSE test_sources "test/test_*.cpp")             # test cpp files
add_executable(test-common ${test_sources})
target_link_libraries(test-common gtest gmock_main lcm rt inih osqp dynacore_param_handler pthread biomimetics)
target_link_libraries(test-common Goldfarb_Optimizer)
target_link_libraries(test-common JCQP)

if(IPOPT_OPTION)
link_directories("../third-party/CoinIpopt/build/lib")
include_directories(SYSTEM "../third-party/CoinIpopt/build/include/coin")
find_library(ipopt NAMES libipopt.so PATHS "../third-party/CoinIpopt/build/lib")
target_link_libraries(test-common ${ipopt})# liblapack blas m dl ipoptamplinterface)
target_link_libraries(test-common WBC_Ctrl)# liblapack blas m dl ipoptamplinterface)
endif(IPOPT_OPTION)

add_test(NAME example_test COMMAND test-common)

endif(CMAKE_SYSTEM_NAME MATCHES Linux)

# Our libraries
add_subdirectory(FootstepPlanner)

