#include "opencv2/core/utility.hpp"
#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/xfeatures2d.hpp"

#include <iostream>
#include <ctype.h>

using namespace cv;
using namespace std;
using namespace xfeatures2d;

int main()
{

    Mat matSrc2 = imread("./data/church02.jpg");
    Mat matSrc3 = imread("./data/church03.jpg");
    cout << "image read success" << endl;
    Mat gray2;
    Mat gray3;
    cvtColor(matSrc2, gray2, COLOR_BGR2GRAY);
    cvtColor(matSrc3, gray3, COLOR_BGR2GRAY);
    Mat descriptors2;
    std::vector<KeyPoint> keypoints2;
    Mat descriptors3;
    std::vector<KeyPoint> keypoints3;
    std::vector<DMatch> matches;
    std::vector<DMatch> good_matches;
    Mat img_matches;

    // 寻找到特征点
    Ptr<ORB> extractor = ORB::create();
    extractor->detectAndCompute(gray2, Mat(), keypoints2, descriptors2);
    extractor->detectAndCompute(gray3, Mat(), keypoints3, descriptors3);

    // 匹配
    BFMatcher matcher(NORM_HAMMING);
    matcher.match(descriptors2, descriptors3, matches);

    // 绘制结果
    drawKeypoints(gray2, keypoints2, gray2, Scalar(0, 0, 255), DrawMatchesFlags::DEFAULT);
    drawKeypoints(gray3, keypoints3, gray3, Scalar(0, 0, 255), DrawMatchesFlags::DEFAULT);
    drawMatches(matSrc2, keypoints2, matSrc3, keypoints3, matches, img_matches);

    // 利用现有数据结构，对比对结构进行筛选
    double max_dist = 0;
    double min_dist = 100;
    // 对现有距离进行排序
    for (int i = 0; i < descriptors2.rows; i++)
    {
        double dist = matches[i].distance;
        if (dist < min_dist)
            min_dist = dist;
        if (dist > max_dist)
            max_dist = dist;
    }

    for (int i = 0; i < descriptors2.rows; i++)
    {
        if (matches[i].distance <= max(2 * min_dist, 0.02))
        {
            good_matches.push_back(matches[i]);
        }
    }
    drawMatches(matSrc2, keypoints2, matSrc3, keypoints3, good_matches, img_matches);
    cout << "good matches: " << good_matches.size() << endl;
    cv::imshow("result", img_matches);
    cv::waitKey(0);
    cv::imwrite("./data/result.jpg", img_matches);
    cv::destroyAllWindows();
};
