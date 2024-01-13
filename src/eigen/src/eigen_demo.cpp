#include <iostream>
#include <cmath>
#include <Eigen/Core>
#include <Eigen/Geometry>
using namespace std;

int main(int argc, char **argv)
{
    Eigen::AngleAxisd rotation_vector(M_PI / 4, Eigen::Vector3d(0, 0, 1));
    cout << "rotation_vector axis = \n"
         << rotation_vector.axis() << endl;
    cout << "rotation_vector angle = \n"
         << rotation_vector.angle() << endl;
    Eigen::Matrix3d rotation_matrix = Eigen::Matrix3d::Identity();
    rotation_matrix << 0.707, -0.707, 0,
        0.707, 0.707, 0,
        0, 0, 1;
    cout << "rotation_matrix = \n"
         << rotation_matrix << endl;

    Eigen::Quaterniond quat = Eigen::Quaterniond(0, 0, 0.383, 0.924);
    cout << "Quaterniond output method 1: \n"
         << quat.coeffs() << endl;
    cout << "Quaterniond output method 2: "
         << "(x,y,z,w) = (" << quat.x() << "," << quat.y() << "," << quat.z() << "," << quat.w() << ") \n";

    rotation_vector.fromRotationMatrix(rotation_matrix);
    cout << "Matrix2Vector method  1: rotation_vector axis = " << rotation_vector.axis() << endl;
    cout << "Matrix2Vector method  1: rotation_vector angle = " << rotation_vector.angle() << endl;

    rotation_vector = rotation_matrix;
    cout << "Matrix2Vector method  2: rotation_vector axis = " << rotation_vector.axis() << endl;
    cout << "Matrix2Vector method  2: rotation_vector angle = " << rotation_vector.angle() << endl;

    rotation_vector = Eigen::AngleAxisd(rotation_matrix);
    cout << "Matrix2Vector method  3: rotation_vector axis = " << rotation_vector.axis() << endl;
    cout << "Matrix2Vector method  3: rotation_vector angle = " << rotation_vector.angle() << endl;

    quat = Eigen::Quaterniond(rotation_matrix);
    cout << "Matrix2Quaterniond method 1 " << quat.coeffs() << endl;

    quat = rotation_matrix;
    cout << "Matrix2Quaterniond method 2 " << quat.coeffs() << endl;

    cout << "Vector2Matrix method 1 " << rotation_vector.matrix() << endl;
    cout << "Vector2Matrix method 2 " << rotation_vector.toRotationMatrix() << endl;

    quat = Eigen::Quaterniond(rotation_vector);
    cout << "Vector2Quaterniond method 1 " << quat.coeffs() << endl;

    rotation_vector = quat;
    cout << "Quaterniond2Vector :"
         << "rotation_vector.axis =" << rotation_vector.axis() << "rotation_vector.angle = " << rotation_vector.angle() << endl;

    rotation_matrix = quat.matrix();
    cout << "Quaterniond2Matrix method 1: " << rotation_matrix << endl;
    rotation_matrix = quat.toRotationMatrix();
    cout << "Quaterniond2Matrix method 2: " << rotation_matrix << endl;
}