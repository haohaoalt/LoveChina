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