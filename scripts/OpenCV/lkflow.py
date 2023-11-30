# -*- coding: utf-8 -*-

"""
@Description :   LK金字塔光流法-python 
@Author      :   ZPILOT 
@Time        :   2023/10/24 16:55:22
"""

import numpy as np
import cv2
import sys

# 创建了一个名为cap的视频捕获对象
# wget https://www.bogotobogo.com/python/OpenCV_Python/images/mean_shift_tracking/slow_traffic_small.mp4
cap = cv2.VideoCapture("slow_traffic_small.mp4")
"""
LK光流法中特征点检测的参数设置
maxCorners最大检测数目
qualityLevel是特征点的质量水平阈值,范围在0到1之间,较高的值表示更高的质量要求
minDistance是特征点之间的最小距离
blockSize是特征点检测中的窗口大小,用于计算特征点的协方差矩阵,这里设置为7,表示窗口大小为7x7像素
""" 
feature_params = dict(maxCorners = 100, qualityLevel = 0.3, minDistance = 7, blockSize = 7)
"""
LK光流法的参数
winSize是光流法中窗口的大小,这里设置15*15像素
maxLevel是金字塔的最大层数,用于多尺度处理,这里是最多使用2层金字塔
criteria是迭代停止的准则,cv2.TERM_CRITERIA_EPS表示通过迭代的误差来停止迭代;
第二个准则cv2.TERM_CRITERIA_COUNT表示通过迭代的次数来停止迭代。具体参数设置为(10, 0.03);
这里表示最多迭代10次或者迭代误差小于0.03时停止迭代
"""
lk_params = dict(winSize = (15, 15), maxLevel = 2, criteria = \
                (cv2.TERM_CRITERIA_EPS | cv2.TERM_CRITERIA_COUNT, 10, 0.03))
# 随机设定颜色
color = np.random.randint(0, 255, (100, 3))
# cap.read()返回两个值，布尔值ret，表示读取是否成功，视频的一帧图像数据，保存在old_frame中
ret, old_frame = cap.read()

# 创建视频编写器
output_file = 'lk_output.mp4'
fourcc = cv2.VideoWriter_fourcc(*'mp4v')
out = cv2.VideoWriter(output_file, fourcc, 30.0, (old_frame.shape[1], old_frame.shape[0]))

old_gray = cv2.cvtColor(old_frame, cv2.COLOR_BGR2GRAY)
# **操作符，传递字典
# 等同于cv2.goodFeaturesToTrack(old_gray, mask=None, maxCorners=100, qualityLevel=0.3, minDistance=7, blockSize=7)
p0 = cv2.goodFeaturesToTrack(old_gray, mask = None, **feature_params)
mask = np.zeros_like(old_frame)

while(1):
    ret, frame = cap.read()
    if frame is None: break
    frame_gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    """
    @brief                  opencv中的金字塔光流法
    @param[in] old_gray     前一帧的灰度图像
    @param[in] frame_gray   当前帧的灰度图像
    @param[in] p0           前一帧中的特征点坐标
    @param[in] None         表示没有前一帧到当前帧的特征点匹配关系
    @param[in] **lk_params  光流计算的参数
    @param[out] p1          当前帧中的特征点坐标
    @param[out] st          特征点跟踪成功的状态(1表示成功,0表示失败)
    @param[out] err         特征点跟踪的误差
    """
    p1, st, err = cv2.calcOpticalFlowPyrLK(old_gray, frame_gray, p0, None, **lk_params)
    good_new = p1[st==1]
    good_old = p0[st==1]

    for i,(new, old) in enumerate(zip(good_new, good_old)):
        a,b = new.ravel()
        c,d = old.ravel()
        mask = cv2.line(mask, (a,b), (c,d), color[i].tolist(), 2)
        frame = cv2.circle(frame, (a,b), 5, color[i].tolist(), -1)
    img = cv2.add(frame, mask)

    # 将处理后的图像写入视频文件
    out.write(img)

    cv2.imshow('LK_Frame', img)
    k = cv2.waitKey(30) & 0xff
    # 摁下Esc键，跳出循环
    if k == 27:
        break
    old_gray = frame_gray.copy()
    p0 = good_new.reshape(-1, 1, 2)

cv2.destroyAllWindows()
cap.release()
out.release()
