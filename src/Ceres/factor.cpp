/*
将Myclass的（）符号的功能定义成了将括号内的数n乘以隐藏参数x倍，其中x是Obj1对象的一个私有成员变量，是是在构造Obj1时候赋予的。因为重载了（）符号，所以在主函数中Obj1这个对象就可以当做一个函数来使用，使用方法为Obj1（n），如果Obj1的内部成员变量_x是5，则此函数功能就是将输入参数扩大5倍，如果这个成员变量是50，Obj1（）函数的功能就是将输入n扩大50倍，这也是仿函数技巧的一个优点，它能利用对象的成员变量来储存更多的函数内部参数。

*/
#include<iostream>
using namespace std;
class Myclass
{
    public:
        Myclass(int x):_x(x){};
        int operator()(const int n)const{
            return n*_x;
        }
    private:
        int _x;
};

int main(){
    Myclass Obj1(5);
    cout << Obj1(3) << endl;
    return 0;
}