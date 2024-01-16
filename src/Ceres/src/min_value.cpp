#include<iostream>
#include<ceres/ceres.h>
#include<ceres/numeric_diff_cost_function.h>

using namespace std;
using namespace ceres;

//第一部分：构建代价函数const function，重载（）符号，仿函数的小技巧
struct CostFunctor {
  // 模板函数，泛化函数类型
  template <typename T>
  // 重载符号（），仿函数；传入待优化变量列表和承接残差的变量列表
  // 一个是待优化的变量x，另一个是残差residual，也就是代价函数的输出
  bool operator()(const T *const x, T *residual) const
  // 三个const意思，从左到右依次是修饰指针不可改变指向的内容，修饰变量x，修饰成员函数，防止成员函数修改被调用对象的值
  {
    //  residual[0] = T(10.0) - x[0];
     residual[0] = T(0.5) * (T(10.0) - x[0]) * (T(10.0) - x[0]); // 1/2(10−x)^2
     return true;
   }
};

struct NumericDiffCostFunctor
{
  // 模板函数，泛化函数类型
  template <typename T>
  // 重载符号（），仿函数；传入待优化变量列表和承接残差的变量列表
  // 一个是待优化的变量x，另一个是残差residual，也就是代价函数的输出
  bool operator()(const T *const x, T *residual) const
  // 三个const意思，从左到右依次是修饰指针不可改变指向的内容，修饰变量x，修饰成员函数，防止成员函数修改被调用对象的值
  {
    //  residual[0] = T(10.0) - x[0];
    residual[0] = T(0.5) * (T(10.0) - x[0]) * (T(10.0) - x[0]); // 1/2(10−x)^2
    return true;
  }
};

//主函数
int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);

  // 寻优参数x的初始值，为5
  double initial_x = 5.0;
  double x = initial_x;

  // 第二部分：通过上一步代价函数构建待求解的优化问题
  // 实例化Problem
  Problem problem;
  // 使用自动求导，将之前的代价函数结构体传入，第一个1是输出维度，即残差的维度，第二个1是输入维度，即待寻优参数x的维度。分别对应之前结构体中的residual和x。
  // CostFunction *cost_function = new AutoDiffCostFunction<CostFunctor, 1, 1>(new CostFunctor); //自动求导法
  CostFunction *cost_function = new NumericDiffCostFunction<NumericDiffCostFunctor, ceres::CENTRAL, 1, 1>(new NumericDiffCostFunctor); // 数值求导法

  // 添加误差项，１、上一步实例化后的代价函数２、核函数３、待优化变量
  problem.AddResidualBlock(cost_function, NULL, &x); // 向问题中添加误差项，本问题比较简单，添加一个就行。（有的问题要不断多次添加ResidualBlock以构建最小二乘求解问题）。这里的参数NULL是指不使用核函数，&x表示x是待寻优参数

  

  // 第三部分： 配置并运行求解器
  Solver::Options options;
  options.linear_solver_type = ceres::DENSE_QR; // 配置增量方程的解法
  options.minimizer_progress_to_stdout = true;  // 输出到cout
  Solver::Summary summary;                      // 优化信息
  Solve(options, &problem, &summary);           // 求解!!!

  std::cout << summary.BriefReport() << "\n"; // 输出优化的简要信息
                                              // 最终结果
  std::cout << "x : " << initial_x
            << " -> " << x << "\n";
  return 0;
}