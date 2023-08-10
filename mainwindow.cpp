#include "mainwindow.h"

#include <QIcon>
#include <QUdpSocket>
#include <QTimer>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QByteArray>
#include <QTextEdit>
#include <QStatusBar>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //main widget
    setWindowIcon(QIcon(":/images/logo.png"));
    mainWidget = new QWidget;
    setCentralWidget(mainWidget);


    //tcp client
    QTcpSocket *tcpSocket = new QTcpSocket;
    tcpSocket->connectToHost(QHostAddress("106.15.62.139"),1234);
    qDebug()<<"connect...";

    //udpsockt bind local tcp port
    QUdpSocket *udpSocket = new QUdpSocket(this);


    connect(tcpSocket,&QTcpSocket::connected,this,[=]{
        qDebug()<<"connect to server";
        qDebug() << tcpSocket->peerAddress().toString();
        qDebug() << tcpSocket->peerPort();
        qDebug() << tcpSocket->peerName();
        qDebug()<<"----------------------";
        qDebug()<<tcpSocket->localAddress();
        qDebug()<<tcpSocket->localPort();

        QStatusBar *bar = statusBar();
        QString info(tcpSocket->localAddress().toString()+":"+QString::number(tcpSocket->localPort()));
        bar->showMessage(info);


        udpSocket->bind(tcpSocket->localPort()); //本地电脑 port <---> 路由器
        qDebug()<<tcpSocket->localPort();



    });

    connect(tcpSocket,&QTcpSocket::readyRead,this,[=]{
        qDebug()<<"read ready";
        qDebug()<<QString(tcpSocket->readAll());
    });





    QVBoxLayout *vboxlayout = new QVBoxLayout;
    QHBoxLayout *hboxlayout = new QHBoxLayout;
    QLineEdit *addrEdit = new QLineEdit;
    QLineEdit *portEdit = new QLineEdit;
    QLineEdit *msgEdit = new QLineEdit;
    QPushButton *button = new QPushButton("send");
    hboxlayout->addWidget(addrEdit);
    hboxlayout->addWidget(portEdit);
    hboxlayout->addWidget(msgEdit);
    hboxlayout->addWidget(button);
    vboxlayout->addLayout(hboxlayout);
    QTextEdit *textEdit = new QTextEdit;
    vboxlayout->addWidget(textEdit);
    centralWidget()->setLayout(vboxlayout);











    QTimer *timer = new QTimer(this);
    //timer->start(1000);

    connect(timer,&QTimer::timeout,this,[=]{
        qDebug()<<"timeout";
        qint64 size = udpSocket->pendingDatagramSize();
        size=100;
        QByteArray msg;
        msg.resize(size);
        QHostAddress addr;
        quint16 port;
        qDebug()<<udpSocket->readDatagram(msg.data(),msg.size(),&addr,&port);
        addrEdit->setText(addr.toString());
        portEdit->setText(QString::number(port));
        textEdit->append(QString::fromLocal8Bit(msg));
    });


    connect(udpSocket,&QUdpSocket::readyRead,this,[=]{
        if(udpSocket->hasPendingDatagrams()){
            qint64 size = udpSocket->pendingDatagramSize();
            QByteArray msg;
            msg.resize(size);
            QHostAddress addr;
            quint16 port;
            udpSocket->readDatagram(msg.data(),msg.size(),&addr,&port);
            addrEdit->setText(addr.toString());
            portEdit->setText(QString::number(port));
            textEdit->append(QString::fromLocal8Bit(msg));
        }
        else{
            qDebug()<<"not padding";
        }

    });











}

MainWindow::~MainWindow()
{
}




