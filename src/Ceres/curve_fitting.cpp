#include <iostream>
#include <opencv2/core/core.hpp>
#include <ceres/ceres.h>
using namespace std;
using namespace cv;

// 构建代价函数结构体，abc为待优化参数，residual为残差。
// 比之前稍微复杂一点的地方就在于计算单个点的残差时需要输入该点的x，y坐标
struct CURVE_FITTING_COST
{
    CURVE_FITTING_COST(double x, double y) : _x(x), _y(y) {}
    template <typename T>
    bool operator()(const T *const abc, T *residual) const
    {
        residual[0] = _y - ceres::exp(abc[0] * _x * _x + abc[1] * _x + abc[2]);
        return true;
    }
    const double _x, _y; // 与之前不同的是结构体内部有_x，_y成员变量，用于储存散点的坐标
};

// 主函数
int main()
{
    // 参数初始化设置，abc初始化为0，白噪声方差为1（使用OpenCV的随机数产生器）。
    double a = 3, b = 2, c = 1;
    double w = 1;
    RNG rng;
    double abc[3] = {0, 0, 0};

    // 生成待拟合曲线的数据散点，储存在Vector里，x_data，y_data。
    vector<double> x_data, y_data;
    for (int i = 0; i < 1000; i++)
    {
        double x = i / 1000.0;
        x_data.push_back(x);
        y_data.push_back(exp(a * x * x + b * x + c) + rng.gaussian(w));
    }

    // 反复使用AddResidualBlock方法（逐个散点，反复1000次）
    // 将每个点的残差累计求和构建最小二乘优化式
    // 不使用核函数，待优化参数是abc
    ceres::Problem problem;
    for (int i = 0; i < 1000; i++)
    {
        problem.AddResidualBlock(
            new ceres::AutoDiffCostFunction<CURVE_FITTING_COST, 1, 3>(
                new CURVE_FITTING_COST(x_data[i], y_data[i])),
            // nullptr,
            new ceres::CauchyLoss(0.5),
            // Ceres库中提供的核函数主要有：TrivialLoss 、HuberLoss、 SoftLOneLoss 、 CauchyLoss。
            // 比如此时要使用CauchyLoss，只需要将nullptr换成new CauchyLoss(0.5) 就行（0 .5为参数）
            abc);
    }

    // 配置求解器并求解，输出结果
    ceres::Solver::Options options;
    options.linear_solver_type = ceres::DENSE_QR;
    options.minimizer_progress_to_stdout = true;
    ceres::Solver::Summary summary;
    ceres::Solve(options, &problem, &summary);
    cout << "a= " << abc[0] << endl;
    cout << "b= " << abc[1] << endl;
    cout << "c= " << abc[2] << endl;
    return 0;
}