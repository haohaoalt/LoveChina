include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
# subdirectory CMakeLists.txt 文件中
message("subdirectory: ${CMAKE_CURRENT_SOURCE_DIR}")

ADD_EXECUTABLE(cvversion src/version.cpp )
target_link_libraries(cvversion ${OpenCV_LIBS})

# # 添加可执行文件 链接OpenCV库
add_executable(LKOpticalFlow src/lkdemo.cpp)
target_link_libraries(LKOpticalFlow ${OpenCV_LIBS})

add_executable(orb_feature src/orb_feature.cpp)
target_link_libraries(orb_feature ${OpenCV_LIBS})

add_executable(record_usb_img src/record_usb_img.cpp)
target_link_libraries(record_usb_img ${OpenCV_LIBS})

# #获取代码，在项目中，将所有代码都放在src文件夹中
# AUX_SOURCE_DIRECTORY(src DIR_SRCS)
# MESSAGE(STATUS "Src file: ${DIR_SRCS}")
# #编译可执行程序
# ADD_EXECUTABLE(${PROJECT_NAME} ${DIR_SRCS})
# #添加链接库
# TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${OpenCV_LIBS})

add_executable(rail-inspection src/rail-inspection.cpp)
target_link_libraries(rail-inspection ${OpenCV_LIBS})

add_executable(image-stitching src/image-stitching.cpp)
target_link_libraries(image-stitching ${OpenCV_LIBS})

add_library(slam_orb src/ORBextractor.cc)
target_link_libraries(slam_orb ${OpenCV_LIBRARIES})

add_executable(orb_compare src/orb_compare.cc)
target_link_libraries(orb_compare slam_orb)

add_library(aruco src/aruco.cpp)
target_link_libraries(aruco ${OpenCV_LIBRARIES})

add_executable(generate_marker src/generate_marker_demo.cpp)
target_link_libraries(generate_marker aruco)

add_executable(estimate_pose src/estimate_pose_demo.cpp)
target_link_libraries(estimate_pose aruco)

add_executable(calibrator src/camera_calibration.cpp)
target_link_libraries(calibrator ${OpenCV_LIBRARIES})