#注意，在一个大工程里，这几个开关一定要尽量放在前面打开，否则有可能会报无法生成ui文件的错误
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
#注意，在一个大工程里，这几个开关一定要尽量放在前面打开，否则有可能会报无法生成ui文件的错误
#set(CMAKE_PREFIX_PATH "~/Qt5.9.9/5.9.9/gcc_64/")#为了不在Qt creator这个软件中也能CMake找到Qt的库

# 1 find qt
find_package(Qt5 COMPONENTS Widgets Gui REQUIRED)
#get_target_property(QtCore_location Qt5::Widgets LOCATION)
find_package(Qt5 COMPONENTS Core REQUIRED)
#get_target_property(QtCore_location Qt5::Core LOCATION)
find_package(Qt5 COMPONENTS SerialPort REQUIRED)

#find_package(pthread REQUIRED)
# Add an executable
#生成可执行文件

# add exe
add_executable(qtserial main.cpp Serial.cpp Serial.h Serial.ui)
#
target_link_libraries(qtserial Qt5::Core Qt5::Widgets Qt5::Gui Qt5::SerialPort)

target_link_directories(qtserial PUBLIC
    ${OpenCV_LIB_DIRS}
    )
target_link_libraries(qtserial
    ${OpenCV_LIBS}
    )
target_include_directories(qtserial PUBLIC
    ${OpenCV_INCLUDE_DIRS}
)