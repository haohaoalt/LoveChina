cmake_minimum_required(VERSION 3.10)

project(learning_to_create_project)

message("\n #### I love China! #### \n")

set(CMAKE_CXX_STANDARD 11)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

find_package(OpenCV 3 REQUIRED)

find_package(Pangolin REQUIRED)

include_directories(
        ${PROJECT_SOURCE_DIR}/include/
)
include_directories(${Pangolin_INCLUDE_DIRS})

add_library(${PROJECT_NAME} SHARED
        src/China.cpp
        src/i.cpp
        src/love.cpp
)

add_executable(i_love_China example/i_love_China.cpp)
target_link_libraries(i_love_China
        ${OpenCV_LIBS}
        ${PROJECT_NAME}
)

# 添加可执行文件
add_executable(LKOpticalFlow src/OpenCV/lkdemo.cpp)

# Pangolin demo
add_executable(Pangolindemo src/Pangolin/Pangolin_demo.cpp)

# 链接OpenCV库
target_link_libraries(LKOpticalFlow ${OpenCV_LIBS})

target_link_libraries(Pangolindemo ${Pangolin_LIBRARIES}) #改成自己的项目名