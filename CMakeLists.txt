cmake_minimum_required(VERSION 3.10)

project(learning_to_create_project)

message("\n #### I love China! #### \n")

set(CMAKE_CXX_STANDARD 14)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set(OpenCV_DIR "/home/hayden/App/opencv345/Install/share/OpenCV")
find_package(OpenCV 3 REQUIRED)
MESSAGE(STATUS "OpenCV version: ${OpenCV_VERSION}")


find_package(Pangolin REQUIRED)

find_package(Ceres REQUIRED)

include_directories(
        ${PROJECT_SOURCE_DIR}/include/
)
include_directories(${Pangolin_INCLUDE_DIRS})

include_directories(${CERES_INCLUDE_DIRS})

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
add_executable(orb_feature src/OpenCV/orb_feature.cpp)


# Pangolin demo
add_executable(Pangolindemo src/Pangolin/Pangolin_demo.cpp)

# Ceres demo
add_executable(min_value src/Ceres/min_value.cpp)
add_executable(curve_fitting src/Ceres/curve_fitting.cpp)
# 链接OpenCV库
target_link_libraries(LKOpticalFlow ${OpenCV_LIBS})

target_link_libraries(Pangolindemo ${Pangolin_LIBRARIES}) #改成自己的项目名

target_link_libraries(min_value ${CERES_LIBRARIES})

target_link_libraries(curve_fitting ${CERES_LIBRARIES} ${OpenCV_LIBS})

target_link_libraries(orb_feature ${OpenCV_LIBS})
