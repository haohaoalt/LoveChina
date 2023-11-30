/*
@Description :   LK金字塔光流法-c++ 
@Author      :   ZPILOT 
@Time        :   2023/10/24 16:55:57
*/

#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>

int main() {
    // 打开视频文件
    cv::VideoCapture cap("slow_traffic_small.mp4");
    if (!cap.isOpened()) {
        std::cout << "Can not open mp4 file" << std::endl;
        return -1;
    }

    cv::Mat old_frame, old_gray;
    std::vector<cv::Point2f> old_points, new_points;
    cv::TermCriteria criteria(cv::TermCriteria::COUNT | cv::TermCriteria::EPS, 10, 0.03);
    double scale = 0.5;

    // 读取第一帧并进行初始处理
    cap >> old_frame;
    cv::resize(old_frame, old_frame, cv::Size(), scale, scale);
    cv::cvtColor(old_frame, old_gray, cv::COLOR_BGR2GRAY);
    cv::goodFeaturesToTrack(old_gray, old_points, 1000, 0.01, 10);

    cv::Mat frame, frame_gray;
    std::vector<uchar> status;
    std::vector<float> error;

    // 创建视频编写器
    // cv::VideoWriter writer;
    // writer.open("lk_output.mp4", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 25, frame.size());

    while (true) {
        cap >> frame;
        if (frame.empty())
            break;
        
        // 调整帧大小并将其转换为灰度图像
        cv::resize(frame, frame, cv::Size(), scale, scale);
        cv::cvtColor(frame, frame_gray, cv::COLOR_BGR2GRAY);

        // 计算稀疏光流
        cv::calcOpticalFlowPyrLK(old_gray, frame_gray, old_points, new_points, status, error, cv::Size(15, 15), 2, criteria);

        // 绘制光流轨迹
        for (size_t i = 0; i < new_points.size(); i++) {
            if (status[i] == 1) {
                cv::line(frame, old_points[i], new_points[i], cv::Scalar(0, 0, 255), 2);
                cv::circle(frame, new_points[i], 3, cv::Scalar(0, 255, 0), -1);
            }
        }

        // 写入当前帧到视频文件
        // writer.write(frame);

        // 显示结果
        cv::imshow("LK_Frame", frame);

        // 按下Esc键退出循环
        if (cv::waitKey(30) == 27)
            break;

        // 更新变量
        std::swap(old_gray, frame_gray);
        std::swap(old_points, new_points);
    }

    // 释放资源
    cap.release();
    cv::destroyAllWindows();
    // 释放视频编写器
    // writer.release();   

    return 0;
}

