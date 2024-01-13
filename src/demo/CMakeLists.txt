include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
# subdirectory CMakeLists.txt 文件中
message("subdirectory: ${CMAKE_CURRENT_SOURCE_DIR}")

add_library(${PROJECT_NAME}_demo SHARED
        src/China.cpp
        src/i.cpp
        src/love.cpp
)

add_executable(i_love_China src/i_love_China.cpp)
target_link_libraries(i_love_China
        ${OpenCV_LIBS}
        ${PROJECT_NAME}_demo
)