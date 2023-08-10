#include "mainwindow.h"

#include <QIcon>
#include <QUdpSocket>
#include <QTimer>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QByteArray>


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


    connect(tcpSocket,&QTcpSocket::connected,this,[=]{
        qDebug()<<"connect to server";
        qDebug() << tcpSocket->peerAddress().toString();
        qDebug() << tcpSocket->peerPort();
        qDebug() << tcpSocket->peerName();
        qDebug()<<"----------------------";
        qDebug()<<tcpSocket->localAddress();
        qDebug()<<tcpSocket->localPort();

    });

    connect(tcpSocket,&QTcpSocket::readyRead,this,[=]{
        qDebug()<<"read ready";
        qDebug()<<QString(tcpSocket->readAll());
    });





    QHBoxLayout *hboxlayout = new QHBoxLayout;
    QLineEdit *addrEdit = new QLineEdit;
    QLineEdit *portEdit = new QLineEdit;
    QLineEdit *msgEdit = new QLineEdit;
    QPushButton *button = new QPushButton("send");
    hboxlayout->addWidget(addrEdit);
    hboxlayout->addWidget(portEdit);
    hboxlayout->addWidget(msgEdit);
    hboxlayout->addWidget(button);
    centralWidget()->setLayout(hboxlayout);




    //udp + bind
    QUdpSocket *udpSocket = new QUdpSocket(this);
    udpSocket->bind(tcpSocket->localPort());
    QHostAddress addr(addrEdit->text());
    quint16 port = portEdit->text().toUInt();
    QByteArray byteArray = msgEdit->text().toLocal8Bit();

    connect(button,&QPushButton::clicked,this,[=]{
        udpSocket->writeDatagram(byteArray,addr,port);
    });






}

MainWindow::~MainWindow()
{
}




