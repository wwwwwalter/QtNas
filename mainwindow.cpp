#include "mainwindow.h"

#include <QIcon>


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


    connect(tcpSocket,&QTcpSocket::connected,[=]{
        qDebug()<<"connect to server";
        qDebug() << tcpSocket->peerAddress().toString();
        qDebug() << tcpSocket->peerPort();
        qDebug() << tcpSocket->peerName();
        qDebug()<<"----------------------";
        qDebug()<<tcpSocket->localAddress();
        qDebug()<<tcpSocket->localPort();

    });

    connect(tcpSocket,&QTcpSocket::readyRead,[=]{
        qDebug()<<"read ready";
        qDebug()<<QString(tcpSocket->readAll());
    });





}

MainWindow::~MainWindow()
{
}




