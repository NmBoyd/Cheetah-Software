cmake_minimum_required(VERSION 3.5)
project(robot)

include_directories(${CMAKE_BINARY_DIR})
include_directories("include/")
include_directories("./")
include_directories("../common/include/")
include_directories("../third-party")
include_directories("../third-party/ParamHandler")
include_directories("../third-party/vectornav/include")
include_directories("../third-party/vectornav/include/vn")
include_directories("../third-party/lord_imu/Include")

include_directories("../lcm-types/cpp")
include_directories("/usr/local/include/lcm/")   # lcm includes

file(GLOB sources "src/*.cpp" "src/rt/*.c"  "src/rt/*.cpp")

add_library(robot SHARED ${sources})

target_link_libraries(robot biomimetics pthread lcm inih dynacore_param_handler lord_imu)
if(CMAKE_SYSTEM_NAME MATCHES Linux)
target_link_libraries(robot libvnc rt)
endif()
