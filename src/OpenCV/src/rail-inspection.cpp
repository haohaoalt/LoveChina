#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

void GetROI(Mat src, Mat &ROI)
{
    int width = src.cols;
    int height = src.rows;

    // 获取车道ROI区域，只对该部分进行处理
    vector<Point> pts;
    Point ptA((width / 8) * 2, (height / 20) * 19);
    Point ptB((width / 8) * 2, (height / 8) * 7);
    Point ptC((width / 10) * 4, (height / 5) * 3);
    Point ptD((width / 10) * 5, (height / 5) * 3);
    Point ptE((width / 8) * 7, (height / 8) * 7);
    Point ptF((width / 8) * 7, (height / 20) * 19);
    pts = {ptA, ptB, ptC, ptD, ptE, ptF};

    // opencv4版本 fillPoly需要使用vector<vector<Point>>
    vector<vector<Point>> ppts;
    ppts.push_back(pts);

    Mat mask = Mat::zeros(src.size(), src.type());
    fillPoly(mask, ppts, Scalar::all(255));

    src.copyTo(ROI, mask);
}

void DetectRoadLine(Mat src, Mat &ROI)
{
    Mat gray;
    cvtColor(ROI, gray, COLOR_BGR2GRAY);

    Mat thresh;
    threshold(gray, thresh, 180, 255, THRESH_BINARY);

    vector<Point> left_line;
    vector<Point> right_line;

    // 左车道线
    for (int i = 0; i < thresh.cols / 2; i++)
    {
        for (int j = thresh.rows / 2; j < thresh.rows; j++)
        {
            if (thresh.at<uchar>(j, i) == 255)
            {
                left_line.push_back(Point(i, j));
            }
        }
    }
    // 右车道线
    for (int i = thresh.cols / 2; i < thresh.cols; i++)
    {
        for (int j = thresh.rows / 2; j < thresh.rows; j++)
        {
            if (thresh.at<uchar>(j, i) == 255)
            {
                right_line.push_back(Point(i, j));
            }
        }
    }

    // 车道绘制
    if (left_line.size() > 0 && right_line.size() > 0)
    {
        Point B_L = (left_line[0]);
        Point T_L = (left_line[left_line.size() - 1]);
        Point T_R = (right_line[0]);
        Point B_R = (right_line[right_line.size() - 1]);

        circle(src, B_L, 10, Scalar(0, 0, 255), -1);
        circle(src, T_L, 10, Scalar(0, 255, 0), -1);
        circle(src, T_R, 10, Scalar(255, 0, 0), -1);
        circle(src, B_R, 10, Scalar(0, 255, 255), -1);

        line(src, Point(B_L), Point(T_L), Scalar(0, 255, 0), 10);
        line(src, Point(T_R), Point(B_R), Scalar(0, 255, 0), 10);

        vector<Point> pts;
        pts = {B_L, T_L, T_R, B_R};
        vector<vector<Point>> ppts;
        ppts.push_back(pts);
        fillPoly(src, ppts, Scalar(133, 230, 238));
    }
}

int main()
{

    VideoCapture capture;
    capture.open("../data/common/Input_Video.mp4");

    if (!capture.isOpened())
    {
        cout << "Can not open video file!" << endl;
        system("pause");
        return -1;
    }

    Mat frame, image;
    while (capture.read(frame))
    {
        char key = waitKey(10);
        if (key == 27)
        {
            break;
        }
        GetROI(frame, image);

        DetectRoadLine(frame, image);

        imshow("frame", frame);
    }

    capture.release();
    destroyAllWindows();
    system("pause");
    return 0;
}
