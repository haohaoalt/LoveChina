cmake_minimum_required(VERSION 3.10)

project(learning_to_create_project)

message("\n #### I love China! #### \n")

set(CMAKE_CXX_STANDARD 14)

message(STATUS "PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
message(STATUS "LIBRARY_OUTPUT_PATH: " ${LIBRARY_OUTPUT_PATH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
message(STATUS "CMAKE_RUNTIME_OUTPUT_DIRECTORY: " ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})


#eigen
set(EIGEN3_INCLUDE_DIR " ${PROJECT_SOURCE_DIR}/thirdparty/eigen-3.3.8/")
include_directories(${EIGEN3_INCLUDE_DIR})
message(STATUS "Found Eigen3: " ${EIGEN3_INCLUDE_DIR})


add_subdirectory(src/eigen)
add_subdirectory(src/OpenCV)

# find_package(Eigen3 REQUIRED)
# if((Eigen3_FOUND) AND (DEFINED EIGEN3_INCLUDE_DIR))
#  message(STATUS "Found Eigen3: " ${EIGEN3_INCLUDE_DIR})
#  INCLUDE_DIRECTORIES(${EIGEN3_INCLUDE_DIR})
# else()
#  message(FATAL_ERROR "EIGEN3 not found.")
# endif()

# set(OpenCV_DIR "/home/hayden/App/opencv345/Install/share/OpenCV")
find_package(OpenCV REQUIRED)
#打印调试信息
MESSAGE(STATUS "Project: ${PROJECT_NAME}")
MESSAGE(STATUS "OpenCV library status:")
MESSAGE(STATUS "    version: ${OpenCV_VERSION}")
MESSAGE(STATUS "    libraries: ${OpenCV_LIBS}")
MESSAGE(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")


# find_package(Pangolin REQUIRED)

# find_package(Ceres REQUIRED)

include_directories(
        ${PROJECT_SOURCE_DIR}/include/
)
# include_directories(${Pangolin_INCLUDE_DIRS})

# include_directories(${CERES_INCLUDE_DIRS})

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




# # Pangolin demo
# add_executable(Pangolindemo src/Pangolin/Pangolin_demo.cpp)

# # Ceres demo
# add_executable(min_value src/Ceres/min_value.cpp)
# add_executable(curve_fitting src/Ceres/curve_fitting.cpp)


# target_link_libraries(Pangolindemo ${Pangolin_LIBRARIES}) #改成自己的项目名

# target_link_libraries(min_value ${CERES_LIBRARIES})

# target_link_libraries(curve_fitting ${CERES_LIBRARIES} ${OpenCV_LIBS})


