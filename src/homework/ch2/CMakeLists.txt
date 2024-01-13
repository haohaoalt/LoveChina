add_executable(motion motion.cc)
target_link_libraries(motion
        ${PROJECT_NAME}.common
        ${PROJECT_NAME}.tools
        )

add_executable(motion_hw motion_hw.cpp)
target_link_libraries(motion_hw
        ${PROJECT_NAME}.common
        ${PROJECT_NAME}.tools
        )
