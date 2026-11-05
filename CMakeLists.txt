cmake_minimum_required(VERSION 3.16)
project(ACC_cluster_GUI C CXX)

set(CMAKE_CXX_STANDARD 17)

set(LV_CONF_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lv_conf.h CACHE STRING "" FORCE)
add_definitions(-DLV_CONF_INCLUDE_SIMPLE)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_subdirectory(lvgl)

set(SOURCES
    src/main.cpp
    src/ui/cluster_view.cpp
)

add_executable(Cluster_GUI ${SOURCES})
target_link_libraries(Cluster_GUI PRIVATE lvgl)

if(NOT CMAKE_CROSSCOMPILING)
    find_package(SDL2 REQUIRED)
    target_include_directories(Cluster_GUI PRIVATE ${SDL2_INCLUDE_DIRS})
    target_link_libraries(Cluster_GUI PRIVATE ${SDL2_LIBRARIES})
    target_compile_definitions(Cluster_GUI PRIVATE USE_SDL=1)
else()
    target_compile_definitions(Cluster_GUI PRIVATE USE_LINUX_EMBEDDED=1)
endif()