# # 添加可执行文件
add_executable(LKOpticalFlow src/lkdemo.cpp)
add_executable(orb_feature src/orb_feature.cpp)

# # 链接OpenCV库
target_link_libraries(LKOpticalFlow ${OpenCV_LIBS})
target_link_libraries(orb_feature ${OpenCV_LIBS})