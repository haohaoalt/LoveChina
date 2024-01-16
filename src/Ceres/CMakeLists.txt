# # Ceres demo
add_executable(min_value src/min_value.cpp)
add_executable(curve_fitting src/curve_fitting.cpp)




target_link_libraries(min_value ${CERES_LIBRARIES} glog)

target_link_libraries(curve_fitting ${CERES_LIBRARIES} ${OpenCV_LIBS})
