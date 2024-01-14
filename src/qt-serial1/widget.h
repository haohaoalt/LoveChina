#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtSerialPort>
#include <QSerialPortInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();  
    int Times,portTime,lineEditData;
private:
    Ui::Widget *ui;
    QSerialPort *serial;                    //串口端口
    QTimer *timer;                          //定时器
    QString Sendtext,Receivetext;           //发送、接收缓存区
    long int SendByte,ReceByte;             //发送、接收字符数
    QStringList portStringLine;             //端口链表

private slots:

    void serialPort_readyRead();            //串口接收
    void TimerEvent();                      //定时发送、更新串口
    void on_pushButton_clicked();           //扫描串口
    void on_pushButton_2_clicked();         //打开串口键按下
    void on_pushButton_7_clicked();         //串口发送
    void on_pushButton_8_clicked();         //清除计数
    void on_pushButton_4_clicked();         //清除接收区
    void on_pushButton_6_clicked();         //清除发送区
    void on_checkBox_clicked();             //文本接收
    void on_checkBox_2_clicked();           //十六进制接收
    void on_checkBox_3_clicked();           //暂停接收
    void on_checkBox_4_clicked();           //文本发送
    void on_checkBox_5_clicked();           //十六进制发送
    void on_pushButton_5_clicked();         //打开文件
    void on_pushButton_3_clicked();         //保存文件
    void on_lineEdit_editingFinished();     //输入定时时间
};
#endif // WIDGET_H
