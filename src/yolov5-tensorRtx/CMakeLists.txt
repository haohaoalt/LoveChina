if(WIN32)
enable_language(CUDA)
endif(WIN32)
add_definitions(-w)
include_directories(${PROJECT_SOURCE_DIR}/include)
# include and link dirs of cuda and tensorrt, you need adapt them if yours are different

# tensorrt
include_directories(/home/hayden/app/TensorRT-8.0.0.3/include)
link_directories(/home/hayden/app/TensorRT-8.0.0.3/targets/x86_64-linux-gnu/lib)


#cuda_add_library(myplugins SHARED yololayer.cu)
#target_link_libraries(myplugins nvinfer cudart)

cuda_add_executable(yolov5exec calibrator.cpp yolov5.cpp preprocess.cu yololayer.cu)
cuda_add_library(yolov5 SHARED calibrator.cpp yolov5.cpp preprocess.cu yololayer.cu)

# target_link_libraries(yolov5 nvinfer)
# target_link_libraries(yolov5 cudart)
# target_link_libraries(yolov5 myplugins)
# target_link_libraries(yolov5 ${OpenCV_LIBS})

target_link_libraries(yolov5exec
	nvinfer
	cudart
	${OpenCV_LIBS})

target_link_libraries(yolov5
	nvinfer
	cudart
	${OpenCV_LIBS})
