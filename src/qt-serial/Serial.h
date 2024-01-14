#pragma once
#include <QtWidgets/QMainWindow>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QTimer>
#include <QMessageBox>

#include <QSerialPortInfo>
#include <QtSerialPort/QSerialPort>

#include <qdebug.h>
#include <qvector.h>

class Serial : public QMainWindow{
    Q_OBJECT
public:
    Serial(QWidget *parent = nullptr);
    ~Serial();
    void RefreshPort(void);
    void timerEvent(QTimerEvent* e);
    void ReceiveAeraInit(QWidget* parent);
    void SendAeraInit(QWidget* parent);
    void SetupInit(QWidget* parent);
    void BeginUSART(QWidget* parent);

    void USART(QString port, QString baud, QString data, QString stop, QString ch);
private:
    QPlainTextEdit* sendAera;
    QPlainTextEdit* receiveAera;

    QPushButton* sendButton;

    QComboBox* portNumber;
    QComboBox* baudRate;
    QComboBox* dataSize;
    QComboBox* stopSize;
    QComboBox* check;
    QComboBox* receiveMode;
    QComboBox* sendMode;
    QPushButton* startUSART;
    QPushButton* endUSART;

    QSerialPort* serialPort;
    QVector<QString>ports;
};
