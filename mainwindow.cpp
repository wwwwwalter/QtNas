#include "mainwindow.h"

#include <QIcon>
#include <QHostInfo>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //main widget
    setWindowIcon(QIcon(":/images/logo.png"));
    mainWidget = new QWidget;
    setCentralWidget(mainWidget);


    //tcp
    tcpServer = new QTcpServer(this);
    //tcpServer->listen(QHostAddress::Any,8888);
    qDebug()<<"listen...";
    connect(tcpServer,&QTcpServer::newConnection,this,&MainWindow::ConnectToSlave);


    tcpSocket = new QTcpSocket(this);
    tcpSocket->connectToHost(QHostAddress("101.228.78.132"),40700);

    connect(tcpSocket,&QTcpSocket::connected,this,&MainWindow::ConnectTo);





}

MainWindow::~MainWindow()
{
}

void MainWindow::ConnectToSlave()
{
    tcpSocket = tcpServer->nextPendingConnection();
    bool ok = true;
    qDebug()<<tcpSocket->peerAddress().toString().split("::ffff:")[1];
    qDebug()<<tcpSocket->peerPort();
    qDebug()<<tcpSocket->peerName();
    connect(tcpSocket,&QTcpSocket::readyRead,this,&MainWindow::ReadInformation);
}

void MainWindow::ReadInformation()
{
    QByteArray rxData = tcpSocket->readAll();
    qDebug()<<rxData;
}

void MainWindow::ConnectTo()
{
    qDebug()<<"connect";
}



void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug()<<tcpSocket->state();
    tcpSocket->disconnectFromHost();
    qDebug()<<tcpSocket->state();
    tcpSocket->abort();
    qDebug()<<tcpSocket->state();

}



