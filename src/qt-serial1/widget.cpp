#include "widget.h"
#include "ui_widget.h"

#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QTimer>
#include <QStringList>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    resize(800,600);                                //窗口限制

    setWindowTitle("Serial_Port");
    SendByte=0;ReceByte=0;
    serial = new QSerialPort(this);

    ui->comboBox_2->setCurrentIndex(5);             //初始化
    ui->comboBox_3->setCurrentIndex(3);
    ui->comboBox_4->setCurrentIndex(2);
    ui->comboBox_5->setCurrentIndex(0);
    ui->lineEdit->setText("1000");
    ui->checkBox->setCheckState(Qt::Checked);
    ui->checkBox_4->setCheckState(Qt::Checked);
    ui->pushButton_7->setEnabled(false);
    ui->checkBox_7->setEnabled(false);
    connect(serial,SIGNAL(readyRead()),             //信号与槽函数
            this,SLOT(serialPort_readyRead()));

    Times=0;portTime=0;
    lineEditData=1000;

    timer = new QTimer;
    timer->start(1);
    //connect(timer,&QTimer::timeout,this,&Widget::TimerEvent);
    connect(timer,SIGNAL(timeout()),this,SLOT(TimerEvent()));       //信号与槽函数
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_2_clicked()
{
    if(ui->pushButton_2->text()==QString("打开串口"))
    {
        //设置串口名
        serial->setPortName(ui->comboBox->currentText());
        //设置波特率
        serial->setBaudRate(ui->comboBox_2->currentText().toInt());
        //设置数据位
        switch(ui->comboBox_3->currentText().toInt())
        {
        case 5:serial->setDataBits(QSerialPort::Data5);break;
        case 6:serial->setDataBits(QSerialPort::Data6);break;
        case 7:serial->setDataBits(QSerialPort::Data7);break;
        case 8:serial->setDataBits(QSerialPort::Data8);break;
        default:serial->setDataBits(QSerialPort::UnknownDataBits);break;
        }
        //设置奇偶校验位
        switch(ui->comboBox_4->currentIndex())
        {
        case 0:serial->setParity(QSerialPort::EvenParity);break;
        case 1:serial->setParity(QSerialPort::MarkParity);break;
        case 2:serial->setParity(QSerialPort::NoParity);break;
        case 3:serial->setParity(QSerialPort::OddParity);break;
        default:serial->setParity(QSerialPort::UnknownParity);break;
        }
        //设置停止位
        switch (ui->comboBox_5->currentIndex())
        {
        case 0:serial->setStopBits(QSerialPort::OneStop);break;
        case 1:serial->setStopBits(QSerialPort::OneAndHalfStop);break;
        case 2:serial->setStopBits(QSerialPort::TwoStop);break;
        default:serial->setStopBits(QSerialPort::UnknownStopBits);break;
        }
        //设置流控制
        serial->setFlowControl(QSerialPort::NoFlowControl);

        //打开串口
        if(!serial->open(QIODevice::ReadWrite))
        {
            QMessageBox::about(NULL,"提示","无法打开串口");
            return;
        }
        //下拉控件失能
        ui->comboBox->setEnabled(false);
        ui->comboBox_2->setEnabled(false);
        ui->comboBox_3->setEnabled(false);
        ui->comboBox_4->setEnabled(false);
        ui->comboBox_5->setEnabled(false);
        ui->pushButton->setEnabled(false);

        ui->checkBox_7->setEnabled(true);
        ui->pushButton_2->setText(tr("关闭串口"));
        ui->pushButton_7->setEnabled(true);
    }
    else
    {
        //关闭串口
        serial->close();
        //下拉按键使能
        ui->comboBox->setEnabled(true);
        ui->comboBox_2->setEnabled(true);
        ui->comboBox_3->setEnabled(true);
        ui->comboBox_4->setEnabled(true);
        ui->comboBox_5->setEnabled(true);
        ui->pushButton->setEnabled(true);

        ui->checkBox_7->setEnabled(false);
        ui->pushButton_2->setText(tr("打开串口"));
        //发送失能
        ui->pushButton_7->setEnabled(false);
    }
}

void Widget::on_pushButton_clicked()                  //扫描串口
{
    int i,n;
    ui->comboBox->clear();
    portStringLine.clear();
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
        portStringLine +=info.portName();
    n=portStringLine.size();
    for(i=0;i<n;i++)
    {
        serial->setPortName(portStringLine[i]);
        if(!serial->open(QIODevice::ReadWrite))
        {
            portStringLine[i]+="(不可用)";
            QVariant v(0);          //禁用
            ui->comboBox->setItemData(1, v, Qt::UserRole - 1);
        }
        else
        {
            QVariant v(1|32);       //可用
            ui->comboBox->setItemData(1, v, Qt::UserRole - 1);
        }
        serial->close();
    }
    ui->comboBox->addItems(portStringLine);
}

void Widget::serialPort_readyRead()                  //串口接收
{
    int i,length;
    QString lasttext;
    if(ui->checkBox_3->checkState()!=Qt::Checked)
    {
        lasttext=ui->textEdit->toPlainText();
        Receivetext = serial->readAll();
        ReceByte+=Receivetext.length();
        ui->label_10->setText(QString::number(ReceByte));
        if(ui->checkBox_2->checkState()==Qt::Checked)
        {
            Receivetext=Receivetext.toLatin1().toHex();     //字符串转十六进制
            length=Receivetext.length();
            for(i=0;i<=length/2;i++)
            {
                Receivetext.insert((2+3*i),' ');            //插入空格字符串
            }
        }
        else
            Receivetext=Receivetext.toLatin1();
        lasttext=lasttext.append(Receivetext);
        ui->textEdit->setText(lasttext);
    }
}


void Widget::on_pushButton_7_clicked()                          //串口发送
{
    QByteArray bytearray;
    Sendtext=ui->textEdit_2->toPlainText();
    if(ui->checkBox_6->checkState()==Qt::Checked)
        Sendtext += '\n';
    if(ui->checkBox_5->checkState()!=Qt::Checked)
        bytearray = Sendtext.toLatin1();
    else
        bytearray = QByteArray::fromHex(Sendtext.toUtf8());     //十六进制转字符串
    serial->write(bytearray);
    //定长发送
    //serial->write((const char *)param_data,16);
    SendByte+=Sendtext.length();
    ui->label_9->setText(QString::number(SendByte));
    ui->textEdit_2->moveCursor(QTextCursor::End);
}


void Widget::TimerEvent()                                       //定时事件，1ms
{
    int t=500;                                                  //扫描串口时间
    Times++;portTime++;
    if(Times>=lineEditData)                                     //定时发送
    {
        if(ui->checkBox_7->checkState()==Qt::Checked)
            Widget::on_pushButton_7_clicked();
        Times=0;
    }
    if(portTime==t)                                             //定时扫描串口
    {
        QStringList newPortStringList;
        newPortStringList.clear();
        foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
            newPortStringList += info.portName();
        if(newPortStringList.size() != portStringLine.size())
        {
            portStringLine = newPortStringList;
            ui->comboBox->clear();
            ui->comboBox->addItems(portStringLine);
        }
        portTime=0;
    }
}


void Widget::on_pushButton_8_clicked()              //清除计数
{
    SendByte=0;
    ReceByte=0;
    ui->label_9->setText(QString::number(SendByte));
    ui->label_10->setText(QString::number(ReceByte));
}


void Widget::on_pushButton_4_clicked()              //清除接收区
{
    ui->textEdit->clear();
}


void Widget::on_pushButton_6_clicked()              //清除发送区
{
    ui->textEdit_2->clear();
}


void Widget::on_checkBox_clicked()                  //文本接收
{
    ui->checkBox->setCheckState(Qt::Checked);
    ui->checkBox_2->setCheckState(Qt::Unchecked);
    ui->checkBox_3->setCheckState(Qt::Unchecked);
}


void Widget::on_checkBox_2_clicked()                //十六进制接收
{
    ui->checkBox->setCheckState(Qt::Unchecked);
    ui->checkBox_2->setCheckState(Qt::Checked);
    ui->checkBox_3->setCheckState(Qt::Unchecked);
}


void Widget::on_checkBox_3_clicked()                //暂停接收
{
    ui->checkBox->setCheckState(Qt::Unchecked);
    ui->checkBox_2->setCheckState(Qt::Unchecked);
    ui->checkBox_3->setCheckState(Qt::Checked);
}


void Widget::on_checkBox_4_clicked()                //文本发送
{
    ui->checkBox_4->setCheckState(Qt::Checked);
    ui->checkBox_5->setCheckState(Qt::Unchecked);
}


void Widget::on_checkBox_5_clicked()                //十六进制发送
{
    ui->checkBox_4->setCheckState(Qt::Unchecked);
    ui->checkBox_5->setCheckState(Qt::Checked);
}


void Widget::on_pushButton_5_clicked()              //打开文件
{
    QString fileName = QFileDialog::getOpenFileName(this);

    QFile file(fileName);     //新建QFile对象
    if(!file.open(QFile::ReadOnly|QFile::Text))
    {
        QMessageBox::warning(this,tr("多文档编辑器"),
                             tr("无法读取文件 %1:\n%2")
                             .arg(fileName,file.errorString()));
    }
    QTextStream in(&file);    //新建文本流对象
    // 鼠标指针变为等待状态
    QApplication::setOverrideCursor(Qt::WaitCursor);
    //读取文件的全部文本内容，并添加到编辑器中
    ui->textEdit_2->setPlainText(in.readAll());
    //鼠标指针恢复为原来状态
    QApplication::restoreOverrideCursor();
    ui->textEdit->setVisible(true);
}


void Widget::on_pushButton_3_clicked()              //保存文件
{
    QString fileName = QFileDialog::getSaveFileName(this);

    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        // %1和%2分别对应后面arg两个参数，/n起换行的作用
        QMessageBox::warning(this, tr("多文档编辑器"),
                    tr("无法写入文件 %1：/n %2")
                   .arg(fileName, file.errorString()));
    }
    QTextStream out(&file);
    // 鼠标指针变为等待状态
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << ui->textEdit->toPlainText();
    // 鼠标指针恢复原来的状态
    QApplication::restoreOverrideCursor();
}


void Widget::on_lineEdit_editingFinished()          //输入定时时间
{
    if(ui->lineEdit->text().toInt()>0)
        lineEditData=ui->lineEdit->text().toInt();
}

